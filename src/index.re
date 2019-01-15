type req;

type res;

type server;

[@bs.module] external micro : ((req, res) => string) => server = "micro";

[@bs.send] external listen : (server, int) => unit = "listen";

let server = micro((req, res) => "Hello, world!");

listen(server, 1337);