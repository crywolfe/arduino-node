// functions that will be executed when
// typeof handle[pathname] === a function in requestHandlers.
// the handle and function are described in index.js

var fs = require('fs'),
server = require('./server');

function sendInterface(response) {
  console.log("Request handler 'interface' was called.");
  response.writeHead(200, {"Content-Type": "text/html"});
  var html = fs.readFileSync(__dirname + "/pages/index.html");
  var img = fs.readFileSync(__dirname + "/pages/circuits.jpg");
  response.end(html);
}

exports.sendInterface = sendInterface;
