deps: 
	npm install

configure:
	npm run configure

compile:
	npm run build

build: deps configure compile

run-only: 
	npm start

run: build run-only

clean:
	rm -rf node_modules build package-lock.json
