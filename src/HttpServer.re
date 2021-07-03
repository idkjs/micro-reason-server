let port = 5000;
let hostname = "localhost";
let questionParam = "/?question=";
let successParam = "/contact=";

let path = "contact/";
let query = Js.Dict.empty();
Js.Dict.set(query, "success", Js.Json.string("true"));
let expectedUrl: ReasonRouter.url = {
  path: ["contact"],
  hash: "",
  search: "success=true",
};
Js.log(query);
Js.log(expectedUrl);
open ReasonRouter;
let search = resp => {
  Js.log2("search_resp", resp);
  switch (resp) {
  | None => ""
  | Some(resp) =>
    switch (resp) {
    | ""
    | "?" => ""
    | raw =>
      /* remove the preceeding ?, which every search seems to have. */
      Js.log2("raw?", raw);
      // Js.log2("raw?Js.String.sliceToEnd(~from=1)", raw|> Js.String.sliceToEnd(~from=1));
      // raw |> Js.String.sliceToEnd(~from=1);
      raw
    }
  };
};
let search2 = resp => {
  Js.log2("search_resp", resp);
  switch (resp) {
  | None => false
  | Some(resp) =>
    switch (resp) {
    | ""
    | "?" => false
    | raw =>
      /* remove the preceeding ?, which every search seems to have. */
      Js.log2("raw?", raw);
      // Js.log(raw |> Js.String.sliceToEnd(~from=1));
      let x = raw == "success=true" ? true : false;
      Js.log2("raw_x", x);
      x;
    }
  };
};
let create_server = http => {
  let server =
    http##createServer((. req, resp) =>
      if (Js.String.startsWith(successParam, req##url)) {
        Js.log2("req##url?", req##url);
        Js.log2(
          "Js.String.split_successParam",
          Js.String.split(successParam, req##url),
        );
        Js.log2(
          "Js.String.split_successParam->Array.get",
          Js.String.split(successParam, req##url)->Array.get(1),
        );
        let success =
          Js.String.split(successParam, req##url)
          ->Array.get(1)
          ->Js.Global.decodeURI;
 Js.log2("success",success);
 Js.log2("success_req##url",req##url);
        Js.log2("search(Some(req##url)", search(Some(req##url)));
        Js.log2("search(Some(success)): ", search(Some(success)));

        /* Insert your parsing code here */
        // switch (search(Some(success))) {
        // | "success=true" => resp##_end("Success!")
        // | _ => resp##_end("Contact Failed!")
        // };
        search2(Some(success))
          ? resp##_end("Success!") : resp##_end("Contact Failed!");
      } else if (Js.String.startsWith(questionParam, req##url)) {
        let question =
          Js.String.split(questionParam, req##url)
          ->Array.get(1)
          ->Js.Global.decodeURI;

        Js.log(question);

        /* Insert your parsing code here */

        resp##_end("Hello World");
      } else {
        resp##statusCode #= 404;
        resp##_end("Uknown parameter");
      }
    );

  server##listen(port, hostname, () =>
    Js.log(
      "Server running at http://"
      ++ hostname
      ++ ":"
      ++ string_of_int(port)
      ++ "/",
    )
  );
};
Js.log({j|try http://$hostname:$port/?question=AnyoneThere|j});
Js.log({j|try http://$hostname:$port/?contact=success=true|j});
Js.log({j|try http://$hostname:$port/?contact=success=false|j});
create_server(HttpTypes.http);
