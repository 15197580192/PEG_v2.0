# PEG_v2.0
This is a new version of PEG ( Partial Evaluation-based Distributed RDF Graph System ). You could find the original version on the [website](https://bnu05pp.github.io/PEG/index-CN.html).
## How to deploy
### Frontend
#### Install
Modify the baseURL of your frontend application to the port where your backend is running.For example, if your backend is running on "http://ip:18888/api", then edit the baseURL in `config.js` and `utils/request.js` 
```
cd peg-frontend
npm install
npm run build
```
#### Deploy
After installing, you could get the packed packages which could be found at the folder`dist`. Then you could deploy it with nginx.
### Backend
We use mysql to save userinfo. You are supposed to install mysql and connect it in the `db/dbUtil.cpp`
#### Install
```
bash pupup
```
#### Deploy
```
# start the chat server
nohup ./chat_server &
# start the backend server
nohup ./build/server &
```