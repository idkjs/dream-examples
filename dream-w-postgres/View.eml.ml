let render comments request =
  <html>
  <body>

%   comments |> List.iter (fun (_id, comment) ->
      <p><%s comment %></p><% ); %>

    <%s! Dream.form_tag ~action:"/" request %>
      <input name="text" autofocus>
    </form>

  </body>
  </html>
