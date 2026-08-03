import streamlit as st
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
    st.write(f"**Name:** {client.get_name()}")
    st.write(f"**Age:** {client.get_age()}")
    st.write(f"**Address:** {client.get_address()}")
    st.write(f"**Nationality:** {client.get_nationality()}")
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
            st.selectbox("Select a stock to buy",["cat","rat"])


    with tab3:
        st.subheader("Advancing and Simulating Investments")



