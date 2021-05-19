type req;

type res;

type server;
// class type incomingRequest =
//   [@bs]
//   {
//     inherit Node.Stream.readableStream;
//   };
type data;
type openssl;
[@bs.module] external openssl: openssl = "openssl-self-signed-certificate";
[@bs.module "openssl-self-signed-certificate"] external key: string = "key";
[@bs.module "openssl-self-signed-certificate"] external cert: string = "cert";
[@bs.module "openssl-self-signed-certificate"] external passphrase: string = "passphrase";

let key:string = key;
type options = {key:string, cert:string, passphrase:string};
let key:string = key;
let cert:string = cert;
let passphrase:string = passphrase;
let options = {key, cert, passphrase};
[@bs.send]
external getDataFromTestObject:
  (
    openssl,
    ~title:  string,
    ~age:  int,
    ~szn:  string
  ) =>
  string =
  "getData";

let nameOfTestObjekt =
  openssl
  |> getDataFromTestObject(
       ~age= 54,
       ~szn= "444",
       ~title= "Herr",
     );

Js.log2("nameOfTestObjekt:",nameOfTestObjekt);
type run = (~req: MicroTypes.incomingMessage, ~res: MicroTypes.serverResponse, ~fn: MicroTypes.requestHandler) => Js.Promise.t(unit);
type send = (~req: MicroTypes.serverResponse, ~code: int, ~fn: MicroTypes.requestHandler,~data:option(Js.t(data))) => Js.Promise.t(unit);
// ServerResponse, code: number, data?: any
[@bs.module] external micro : ((req, res) => string) => server = "micro";

[@bs.send] external listen : (server, int) => unit = "listen";
