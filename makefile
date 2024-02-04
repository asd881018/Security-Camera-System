C_MODULES= bbg
SERVER= server
FRONTEND = $(SERVER)/frontend

all:
	$(MAKE) app 
	$(MAKE) run
run:
	cd $(FRONTEND) && npm run build
	cd $(SERVER) && node index.js

app:
	cd $(C_MODULES) && $(MAKE) app

install:
	cd $(SERVER) && npm install
	cd $(FRONTEND) && npm install && apt-get npm install --save react-router-dom

clean:
	cd $(C_MODULES) && $(MAKE) clean
