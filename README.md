# SimpleSocketChat

SimpleSocketChat is a simple serwer-client chat application written in python(server) and c++/qt(client). It have very basic funcionalities like chat, password to login, admin password and kicking users.

## How to use chat server?

1. Open `chat_serwer.py` file.
2. Setup Ip and Port on which server will work, by editing this lines of code:

``` python
SERWER_IP = "localhost"
SERWER_PORT = 9999
```
3. Setup serwer name by editing this lines of code:

```python
SERWER_NAME = "server"
```

4. Setup password for login to server and password for login to server for admins, by editing this lines of code:

```python
PASSWORD = "none"
ADMIN_PASSWORD = "none"
```
if you don't want password or admin password just type "none".

5. Run `chat_serwer.py` file.
6. Type `start` to start the server.
7. If you want to kick someone from the server, just type `kick user_name`.

## How to use client?

1. Run `chat_client_gui.exe` file(`client_relase/chat_client_gui.exe`).
2. Click `Add server` and type server login data.
3. If you are connected, just type message and click send to send it.
4. If you want to kick someone, you need to be a admin. If you are admin, select user from the list and click `kick`
5. To disconnect from the server click `disconnect`. 
6. To remove server from the list select it and click `remove server`.

## Contact

Project made by GAMEPLAYER: https://github.com/GamePlayer103
 