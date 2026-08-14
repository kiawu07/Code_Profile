import streamlit as st
import pandas as pd
from models.account import Account
from models.client import Client
from models.invest import Invest

st.set_page_config(
    page_title="KIAGrow Investment Simulator",
    page_icon="📈",
    layout="wide"
)

st.title("KIAGrowTM* Investment Bank Simulator")

with st.expander("About this simulator", expanded=False):
    st.markdown(
    """
    Welcome to the KIAGrowTM* Investment Bank Simulator! This application allows you to simulate banking and investment activities in a risk-free environment. 
    
    **Features:**
    - Create a bank account with a unique account number.
    - Deposit and withdraw funds from your bank account.
    - Transfer money between your bank account and investment account.
    - Buy and sell stocks based on real-time simulated market conditions.
    - Track your portfolio performance over time.
    - Analyze stock trends and market news to make informed investment decisions.
    - Download a personalized report of your account and investment activities.
    - Grow your investment portfolio and monitor your net worth.

    **Disclaimer:** This simulator is for educational purposes only and does not represent real financial advice or investment opportunities. Stocks prices, market conditions, and news are simulated and may not reflect real-world scenarios. Market movements and news are for illustrative purposes only.
    Success in this simulator does not guarantee success in real-world investing. Always seek professional financial advice before making any investment decisions.
    Designed and developed by Alwalid Prince Kiawu.
    """
)

st.sidebar.image("data/logo.png",width = 300)
st.sidebar.divider()
st.sidebar.caption("KIAGrowTM* Investment Bank Simulator")
st.sidebar.caption("Educational simulation • Not financial advice")
#check if client is not in session_state and if not, initialize them and set them to None
if "client" not in st.session_state:
    st.session_state.client = None
    st.session_state.account = None
    st.session_state.invest = None


if st.session_state.client is None:
    st.subheader("Create your account")

    name = st.text_input("Enter your name")
    age = st.number_input("Enter you age", min_value=0, step =1)
    address = st.text_input("Enter your address")
    nationality = st.text_input("Enter your nationality")
    pin = st.number_input("Enter your 4 digit PIN",min_value=0,step=1)

    if st.button("Create Account"):
        client = Client(name,age,address,nationality)
        account = Account(client, pin)
        account.deposit(1000)
        invest = Invest()
        st.balloons()

        st.session_state.client = client
        st.session_state.account = account
        st.session_state.invest = invest
        st.session_state.message = "Account created successfully!"
        st.rerun()


#client is already in session_state so now let's use it for client,account and invest and don't reset
else:
    #retrieving previous data that was in session state
    client = st.session_state.client
    account = st.session_state.account
    invest = st.session_state.invest

    st.subheader("📊Dashboard")


    st.divider()


    col1, col2 = st.columns(2)

    with col1:
        st.markdown("### 👤 Client Information")
        st.write(f"**Name:**  {client.get_name()}")
        st.write(f"**Age:**  {client.get_age()}")
        st.write(f"**Nationality:**  {client.get_nationality()}")
        st.write(f"**Address:**  {client.get_address()}")

    with col2:
        st.markdown("### 🏦 Banking Information")
        st.write(f"**Account Number:**  {account.get_account_num()}")
        with open("data/info.txt","rb") as file:
            st.download_button(label = "Download my info",
                data = file,
                file_name = "info.txt",
                mime = "text/plain")

    st.divider()

    col5,col6,col7 = st.columns(3)

    with col5:
        st.metric("💵 Bank Balance",f"${account.get_balance():,.2f}")

    with col6:
        st.metric("💰 Available to Trade",f"${invest.get_available_to_trade():,.2f}")

    with col7:
        st.metric("📈 Investment Net Worth", f"${invest.networth():,.2f}")

        #sucess message
    if "message" in st.session_state:
        st.success(st.session_state.message)
        del st.session_state.message

    #tabs
    tab1, tab2, tab3 = st.tabs(["💰Transfer Money", "📈Invest in Stocks","📊Portfolio Analytics"])


    with tab1:
        st.subheader("Transfer Money to/from accounts")
        direction = st.radio("Transfer Direction",["Bank to Investment","Investment to Bank"])
        amount = st.number_input("How much would you like to tranfer")
        pin_input = st.number_input("Enter your PIN",min_value=0,step=1)

        if st.button("Tranfer Money"):
            try:
                if direction == "Bank to Investment":
                    invest.transfer_to_trade(account, amount, pin_input)
                else:
                    invest.transfer_to_bank(account,amount,pin_input)
                st.session_state.message = f"Tranfered ${amount:.2f} successfully"
                st.rerun()
            except Exception as e:
                st.error(str(e))


    with tab2:
        st.subheader("Buy/Sell Stocks")
        direction = st.radio("Invest Direction",["Buy stocks","Sell stocks"])

        if direction == "Buy stocks":
            df =  pd.DataFrame([{"Name":s.name,"Symbol":s.symbol,"Value":s.value,"Volatility(%)":s.volatility}for s in invest.stocks])
            st.dataframe(df)

            choice = st.selectbox("Select the symbol of the stock you wish to buy",[s.symbol for s in invest.stocks])
            stock_index = [s.symbol for s in invest.stocks].index(choice)
            amount = st.number_input("Enter the dollar amount you wish to invest",min_value =0.01)

            if st.button("Execute Buy"):
                try:
                    quantity = invest.execute_buy(stock_index,amount)
                    st.session_state.message = f"Bought {quantity:.4f} shares of {choice} for ${amount:.2f}"
                    st.rerun()
                except Exception as e:
                    st.error(str(e))

        else:

            if len(invest.holdings) == 0:
                st.write("You have no holdings to sell.")
            else:
                df = pd.DataFrame([{"Name":h.name,"Symbol":h.symbol,"Quantity":h.quantity,"Cost Basis":h.cost_basis}for h in invest.holdings])
                df.set_index("Name")
                st.dataframe(df)

                choice = st.selectbox("Select the holding you wish to sell",[h.symbol for h in invest.holdings])
                stock_index = [h.symbol for h in invest.holdings].index(choice)

                sell_all = st.checkbox("Sell all shares")
                if sell_all:
                    quantity = -1
                else:
                    quantity = st.slider("Enter the quantity you wish to sell",min_value = 0.0, max_value = invest.holdings[stock_index].quantity)

                if st.button("Execute Sale"):
                    try:
                        proceeds = invest.execute_sell(stock_index,quantity)
                        st.session_state.message = f"Sold shares of {choice} for ${proceeds:.2f}"
                        st.rerun()
                    except Exception as e:
                        st.error(str(e))

    with tab3:
        st.subheader("Portfolio Analysis")

        with st.container(border = True):
            st.markdown("### Market News")

            if invest.current_news:
                st.info(invest.current_news)
            else:
                st.info("No news available yet. Advance time to see market news.")

        if(len(invest.holdings)) == 0:
            st.write("You have no holdings, buy some stock to view the market")

        else:
            st.markdown("### Current Prices")

            prices = [[h.symbol, f"${invest.get_stock_value(h.symbol):,.2f}", invest.get_percent_change_in_stock_val(h.symbol)]for h in invest.holdings]
            df = pd.DataFrame(prices, columns=["Symbol","Price","Change"])
            st.dataframe(df)

            st.divider()


            col1,col2 = st.columns(2)

            with col1:
                if st.button("Advance a Day"):
                    invest.advance()
                    st.rerun()

            with col2:
                if st.button("Advance 10 days"):
                    for i in range(10):
                        invest.advance()
                    st.rerun()

            if(len(invest.history)) == 0:
                st.write("Advance time to see stock performance")
            else:

                col1,col2 = st.columns(2)

                with col1:
                    st.markdown("### Portfolio Allocation")
                    #pie chart
                    portfolio = [[h.symbol, (h.quantity * invest.get_stock_value(h.symbol))] for h in invest.holdings]
                    df = pd.DataFrame(portfolio, columns=["Stock","Value"])

                    df = df.set_index("Stock")

                    st.pyplot(df.plot.pie(y="Value",autopct = "%1.1f%%",legend = False).figure)

                    st.metric(
                    "📊 Portfolio Value",
                    f"${invest.networth():,.2f}"
                    )


                with col2:
                    st.markdown("### Stock Performance")
                    #line chart
                    df = pd.DataFrame(invest.history)
                    df = df.set_index("Day")
                    st.line_chart(df)
                    st.caption(
                    "Market movements are simulated using stock-specific volatility."
                    )



st.caption("Disclaimer: KIAGrowTM* is a simulation and does not represent real financial advice or investment opportunities. All investments carry risk, and past performance is not indicative of future results. Users are encouraged to seek professional financial advice before making any investment decisions.")
st.sidebar.caption("Made and designed by Alwalid Prince Kiawu")




