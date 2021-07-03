type req;

type res;

type server;

[@bs.module] external micro : ((req, res) => string) => server = "micro";

[@bs.send] external listen : (server, int) => unit = "listen";

let port = 1337;
let add = (a, b) => a + b;

let server = micro((req, res) => "Hello, World" ++ " " ++ string_of_int(add(200, 300)));

// let server = micro((req, res) => "Hello, world!");

Js.log({j|http://localhost:$port/|j})

listen(server, port);
