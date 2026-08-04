import streamlit as st
import pandas as pd
from models.account import Account
from models.client import Client
from models.invest import Invest

st.title("KIAGrowTM* Investment Bank Simulator")

#check if client is not in session_state and if not, initialize them and set them to None
if "client" not in st.session_state:
    st.session_state.client = None
    st.session_state.account = None
    st.session_state.invest = None

if st.session_state.client == None:
    st.subheader("Create your account")

    name = st.text_input("Enter your name")
    age = st.number_input("Enter you age", min_value=0, step =1)
    address = st.text_input("Enter your address")
    nationality = st.text_input("Enter your nationality")
    pin = st.number_input("Enter you 4 digit PIN", min_value = 1000, max_value=9999, step=1)

    if st.button("Create Account"):
        client = Client(name,age,address,nationality)
        account = Account(client, pin)
        account.deposit(1000)
        invest = Invest()

        st.session_state.client = client
        st.session_state.account = account
        st.session_state.invest = invest
        st.rerun()

#client is already in session_state so now let's use it for client,account and invest and don't reset
else:
    #retrieving previous data that was in session state
    client = st.session_state.client
    account = st.session_state.account
    invest = st.session_state.invest

    st.subheader("Dashboard")

    col1,col2 = st.columns(2)

    with col1:
        st.write(f"**Name:** {client.get_name()}")
        st.write(f"**Age:** {client.get_age()}")
        st.write(f"**Address:** {client.get_address()}")
        st.write(f"**Nationality:** {client.get_nationality()}")

    with col2:
        st.write(f"**Bank Account Number:** {account.get_account_num()}")
        st.write(f"**Bank Account Balance:** ${account.get_balance():.2f}")
        st.write(f"**Available to Trade:** ${invest.get_available_to_trade():.2f}")
        st.write(f"**Net Worth:** ${invest.networth():.2f}")

    #tabs
    tab1, tab2, tab3 = st.tabs(["Transfer Money", "Invest in Stocks","Advance Time"])

    with tab1:
        st.subheader("Transfer Money to/from accounts")
        direction = st.radio("Transfer Direction",["Bank to Investment","Investment to Bank"])
        amount = st.number_input("How much would you like to tranfer")
        pin_input = st.number_input("Enter your PIN", min_value=1000, max_value=9999)

        if st.button("Tranfer Money"):
            try:
                if direction == "Bank to Investment":
                    invest.transfer_to_trade(account, amount, pin_input)
                else:
                    invest.transfer_to_bank(account,amount,pin_input)
                st.success(f"Tranfered ${amount:.2f} successfully")
                st.rerun()
            except Exception as e:
                st.error(str(e))


    with tab2:
        st.subheader("Buy/Sell Stocks")
        direction = st.radio("Invest Direction",["Buy stocks","Sell stocks"])

        if direction == "Buy stocks":
            df =  pd.DataFrame([{"Name":s.name,"Symbol":s.symbol,"Value":s.value}for s in invest.stocks])
            st.table(df)

            choice = st.selectbox("Select the symbol of the stock you wish to buy",[s.symbol for s in invest.stocks])
            stock_index = [s.symbol for s in invest.stocks].index(choice)
            amount = st.number_input("Enter the price you wish to pay",min_value =0.01)

            if st.button("Execute Buy"):
                try:
                    quantity = invest.execute_buy(stock_index,amount)
                    st.success(f"Bought {quantity:.4f} shares of {choice} for ${amount:.2f}")
                    st.rerun()
                except Exception as e:
                    st.error(str(e))

        else:

            if len(invest.holdings) == 0:
                st.write("You have no holdings to sell.")
            else:
                df = pd.DataFrame([{"Name":h.name,"Symbol":h.symbol,"Quantity":h.quantity,"Cost Basis":h.cost_basis}for h in invest.holdings])
                st.table(df)

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
                        st.success(f"Sold shares of {choice} for ${proceeds:.2f}")
                        st.rerun()
                    except Exception as e:
                        st.error(str(e))

    with tab3:
        st.subheader("Stock Market")

        if(len(invest.holdings)) == 0:
            st.write("You have no holdings, buy some stock to view the market")

        else:
            st.write("**Current Prices:**")
            prices = [[h.symbol,invest.get_stock_value(h.symbol)]for h in invest.holdings]
            df = pd.DataFrame(prices, columns=["Symbol","Price"])
            st.table(df)

            st.divider()

            if(len(invest.history)) == 0:
                st.write("Advance time to see stock performance")
            else:
                df = pd.DataFrame(invest.history)
                df = df.set_index("Day")
                st.line_chart(df)


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



st.caption("Disclaimer: KIAGrowTM* is a simulation and does not represent real financial advice or investment opportunities. All investments carry risk, and past performance is not indicative of future results. Users are encouraged to seek professional financial advice before making any investment decisions.")
st.caption("Made and designed by Alwalid Prince Kiawu")




