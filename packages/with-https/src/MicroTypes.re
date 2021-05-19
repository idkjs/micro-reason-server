// type incomingMessage;
// type serverResponse;
// type requestListener;
type error;
class type _incomingMessage =
  [@bs]
  {
    pub httpVersion: string;
    pub httpVersionMajor: int;
    pub httpVersionMinor: int;
    pub complete: bool;
    // pub connection: Socket;
    // pub headers: IncomingHttpHeaders;
    pub rawHeaders: array(string);
    pub trailers: (~key: string) => option(string);
    pub rawTrailers: array(string);
    pub setTimeout: [@bs.this] (~msecs: int, ~callback: unit => unit) => unit;
    /**
         * Only valid for request obtained from http.Server.
         */
    pub method: option(string);
    /**
         * Only valid for request obtained from http.Server.
         */
    pub url: option(string);
    /**
         * Only valid for response obtained from http.ClientRequest.
         */
    pub statusCode: option(int);
    /**
         * Only valid for response obtained from http.ClientRequest.
         */
    pub statusMessage: option(string);
    // pub    socket: Socket;
    pub destroy: option(error) => unit;
  };
  // constructor(socket: Socket);
type incomingMessage = Js.t(_incomingMessage);
class type _requestListener =
  [@bs]
  {
    [@bs.get]
    pub url: string;
    pub statusCode: int;
    pub statusMessage: string;
    pub method: string;
    pub httpVersion: string;
  };

type requestListener = Js.t(_requestListener);

class type _serverResponse =
  [@bs]
  {
    [@bs.set]
    pub statusCode: int;
    pub setHeader: (string, string) => unit;
    pub _end: string => unit;
  };

type serverResponse = Js.t(_serverResponse);

[@unboxed]
type any =
  | Any('a): any;
type requestHandler = (~req: incomingMessage, ~res: serverResponse) => any
and serve = (~fn: requestHandler) => requestListener
and run =
  (~req: incomingMessage, ~res: serverResponse, ~fn: requestHandler) =>
  Js.Promise.t(unit);
module Json_info_limit: {
  type t;
  let string: string => t;
  let number: int => t;
} = {
  [@unboxed]
  type t =
    | Any('a): t;
  let string = (v: string) => Any(v);
  let number = (v: int) => Any(v);
};
type json_info_limit = Json_info_limit.t;
type json_info = {
  limit: option(json_info_limit),
  encoding: option(string),
}
and json =
  (~req: incomingMessage, ~info: option(json_info)=?, unit) =>
  Js.Promise.t(unit);

module Text_info_limit: {
  type t;
  let string: string => t;
  let number: int => t;
} = {
  [@unboxed]
  type t =
    | Any('a): t;
  let string = (v: string) => Any(v);
  let number = (v: int) => Any(v);
};
type text_info_limit = Text_info_limit.t;
type text_info = {
  limit: option(text_info_limit),
  encoding: option(string),
}
and text =
  (~req: incomingMessage, ~info: option(text_info)=?, unit) =>
  Js.Promise.t(unit);
module Buffer_info_limit: {
  type t;
  let string: string => t;
  let number: int => t;
} = {
  [@unboxed]
  type t =
    | Any('a): t;
  let string = (v: string) => Any(v);
  let number = (v: int) => Any(v);
};
type buffer_info_limit = Buffer_info_limit.t;
type buffer_info = {
  limit: option(buffer_info_limit),
  encoding: option(string),
}
and buffer =
  (~req: incomingMessage, ~info: option(buffer_info)=?, unit) =>
  Js.Promise.t(unit)
and send =
  (~res: serverResponse, ~code: int, ~data: option(any)=?, unit) =>
  Js.Promise.t(unit)
and createError_return_2 = {
  statusCode: int,
  originalError: option(error),
}
and createError =
  (~code: int, ~msg: string, ~orig: option(error)=?, unit) =>
  (error, createError_return_2)
and sendError_info = {
  statusCode: option(int),
  status: option(int),
  message: option(string),
  stack: option(string),
}
and sendError =
  (~req: incomingMessage, ~res: serverResponse, ~info: sendError_info) =>
  Js.Promise.t(unit)
and default = serve;
