# importing libs
import time
import threading
import socket

# | +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ | #
# | =============================================================== | #
# | ------------ SimpleSocketChat server by GAMEPLAYER ------------ | #
# | =============================================================== | #
# | +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ | #


# | ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ | #
# | ----- Edit this variables to change serwer configuration! ------ | #
# | ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ | #

SERWER_IP = "localhost"
SERWER_PORT = 9999
SERWER_NAME = "server"
PASSWORD = "none"
ADMIN_PASSWORD = "none"

# | ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ | #
# | ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ | #


# | ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ | #
# | ----------------------------- Code ----------------------------- | #
# | ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ | #

# list of clients
clientsList = []
# list of nicknames
clientsNicknamesList = []
# lis of admins
clientIsAdminList = []

# creating new server
server = socket.socket()
# setting up server port and ip
server.bind((SERWER_IP, SERWER_PORT))

# function for listening commands from user


def listenCommands():
    while True:
        # command input
        command = input()
        # command for starting server
        if (command == "start") and (newClientThread.is_alive() == False):
            # starting server
            newClientThread.start()
        # command for kicking user
        if command[0:4] == "kick":
            try:
                # getting nickname index
                nicknameIndex = clientsNicknamesList.index(command[5:])
                # getting client by index
                client = clientsList[nicknameIndex]
                # clossing connection with client
                client.close()
                print("[KICKED] User succesfully kicked.")
            except:
                # printing error
                print("[NOT KICKED] Can't find this user!")
        # command for help
        if command == "help":
            print("You can find help in the readme file.")

# function for sending messages to all clients


def sendMessage(message, prefix):
    message = prefix + message
    for client in clientsList:
        client.send(message.encode())

# function for refreshing users list in clients applications


def refreshUserList():
    sendMessage("nU", "")
    time.sleep(0.05)
    for nickname in clientsNicknamesList:
        sendMessage(nickname, "nA ")
        time.sleep(0.5)
    print("[USERS LIST REFRESHED] Users list succesfully refreshed.")

# function for reciving messages from client


def reciveMessage(client):
    while True:
        # getting client index
        index = clientsList.index(client)
        # getting client nickname by index
        nickname = clientsNicknamesList[index]
        try:
            # reciving message from client
            message = client.recv(1024).decode()
            if message[0] == "m":
                # sending message to all clients
                sendMessage(f'<{nickname}> {message[1:]}', "m")
            if message[0] == "k":
                print("[KICK] User wants to kick other user.")
                # checking than client is admin
                isAdmin = client in clientIsAdminList
                if(isAdmin):
                    # getting the index of the nickanme of kicked client
                    nicknameIndex = clientsNicknamesList.index(message[1:])
                    # getting client by index
                    client = clientsList[nicknameIndex]
                    # clossing connection with client
                    client.close()
                    print("User succesfully kicked.")
                else:
                    # sending error than client havent got admin premissions
                    client.send('kPremission'.encode())
                    print("User haven't got premissions")
        except:
            # removing client from the list when it isn't responding
            isAdmin = client in clientIsAdminList
            # chcehing than client is admin
            if(isAdmin):
                # removing client from admins list
                clientIsAdminList.remove(client)
            # removing client from clients list
            clientsList.remove(client)
            # closing connect with the client
            client.close()
            # removing client nickname from the list
            clientsNicknamesList.remove(nickname)
            # sending message than client left the server to all clients
            # refreshing users list
            refreshUserList()
            sendMessage(f'{nickname} left the server.', "m")
            print(
                f'[DISCONNECTED] {nickname} has been disconnected from teh server.')
            break

# function for adding new clients


def newClient():
    # starting listening for new connections
    server.listen()
    print("[STARTED] Serwer started listening for new connections.")
    while True:
        # accepting new connection
        client, adress = server.accept()
        print(f'[NEW CONNECTION] New connection from adress {adress}.')
        if not PASSWORD == "none":
            # reciving password
            client.send('pSend'.encode())
            print(f'Waiting for password from {adress}...')
            password = client.recv(1024).decode()
            print(f'Password from {adress} is {password}. Checking...')

            # checking password
            if not password == PASSWORD:
                if not ADMIN_PASSWORD == "none":
                    # checking admin password
                    if password == ADMIN_PASSWORD:
                        # adding client to admins list
                        clientIsAdminList.append(client)
                        # sending information than client is admin to client
                        client.send('pAdmin'.encode())
                        print(f'{adress} is admin.')
                    else:
                        # sending information than password is invalid
                        client.send('pInvalid'.encode())
                        # clossing connection with client
                        client.close()
                        print(f'{adress} password is invalid. User disconnected.')
                        continue
                else:
                    # sending information than password is invalid
                    client.send('pInvalid'.encode())
                    # clossing connection with client
                    client.close()
                    print(f'{adress} password is invalid. User disconnected.')
                    continue

        else:
            # reciving password
            client.send('pSend'.encode())
            print(f'Waiting for password from {adress}...')
            password = client.recv(1024).decode()
            print(f'Password from {adress} is {password}. Checking...')
            if not ADMIN_PASSWORD == "none":
                # checking admin password
                if password == ADMIN_PASSWORD:
                    # adding client to admins list
                    clientIsAdminList.append(client)
                    # sending information than client is admin to client
                    client.send('pAdmin'.encode())
                    print(f'{adress} is admin.')

        time.sleep(0.05)
        # reciving nickname
        client.send('nSend'.encode())
        print(f'Waiting for nickname from {adress}...')
        nickname = client.recv(1024).decode()
        print(f'{adress} nickname is {nickname}. Checking than it is valid...')
        # checking than the nickname isn't the same as thee server name
        if nickname == SERWER_NAME:
            # snding information than username is invalid
            client.send('nInvalid'.encode())
            # clossing connection with client
            client.close()
            print(f'{adress} nickname is the same as serwer name. User disconnected.')
            continue
        for saveClient in clientsNicknamesList:
            # checking than client username doesn't exists
            if nickname == saveClient:
                # snding information than username is invalid
                client.send('nInvalid'.encode())
                # clossing connection with client
                client.close()
                print(f'{adress} nickname already exists. User disconnected.')
                continue
        # writing nickname to the list
        clientsNicknamesList.append(nickname)
        # writing client to the list
        clientsList.append(client)
        # creating new thread for client
        thread = threading.Thread(target=reciveMessage, args=[client])
        thread.start()
        # sending message to all clients than client join teh server
        sendMessage(f'{nickname} joined the server chat.', "m")
        print(f'{adress}, {nickname} succesfully joined server chat.')
        time.sleep(0.05)
        # refreshing users list
        refreshUserList()


print("[LOADED] SimpleSocketChat made by GAMEPLAYER is loaded. If you need help please type help.")
newClientThread = threading.Thread(target=newClient)
listenCommands()


# | ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ | #
# | ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ | #
