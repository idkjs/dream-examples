module type DB = Caqti_lwt.CONNECTION;
module R = Caqti_request;
module T = Caqti_type;

let list_comments = {
  let query =
    R.collect(T.unit, T.(tup2(int, string)), "SELECT id, text FROM comment");
  (module Db: DB) => {
    let%lwt comments_or_error = Db.collect_list(query, ());
    Caqti_lwt.or_fail(comments_or_error);
  };
};

let add_comment = {
  let query = R.exec(T.string, "INSERT INTO comment (text) VALUES ($1)");
  (text, module Db: DB) => {
    let%lwt unit_or_error = Db.exec(query, text);
    Caqti_lwt.or_fail(unit_or_error);
  };
};

let render = (comments, request) => View.render(comments, request);
let pool = "postgresql://dream:password@localhost:5432/dream";
let pool2 = "postgresql:///dream";
let () =
  Dream.run(~interface="0.0.0.0") @@
  Dream.logger @@
  Dream.sql_pool(pool) @@
  Dream.sql_sessions @@
  Dream.router([
    Dream.get("/", request =>{
      let%lwt comments = Dream.sql(request, list_comments);
      Dream.html(render(comments, request));
    }),
    Dream.post("/", request =>
      switch%lwt (Dream.form(request)) {
      | `Ok([("text", text)]) =>
        let%lwt () = Dream.sql(request, add_comment(text));
        Dream.redirect(request, "/");
      | _ => Dream.empty(`Bad_Request)
      }
    ),
  ]) @@
  Dream.not_found;
