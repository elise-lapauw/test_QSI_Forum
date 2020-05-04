type repository = {
  idmessage: string,
  texte: string,
  dateenvoi: string,
  idcours: string,
  auteur: string,
  nblikes: string,
  isliked: string,
};

type list_of_repos = list(repository);

type state = {
  input: string,
  utilisateur: string,
  text: string,
  isLoading: bool,
  results: list_of_repos,
};

type action =
  | UpdateInput(string, string)
  | UpdateMes
  | UpdateText(string)
  | UpdateResults(list_of_repos)
  | Search /* global app state   TODO: replace the isLoading boolean with variants*/;

let initialAppState = {
  input: "",
  utilisateur: "",
  text: "",
  isLoading: false,
  results: [],
};

module Api = {
  let decodeItem = json =>
    Json.Decode.{
      idmessage: json |> field("idmessage", string),
      texte: json |> field("texte", string),
      dateenvoi: json |> field("dateenvoi", string),
      idcours: json |> field("idcours", string),
      auteur: json |> field("auteur", string),
      nblikes: json |> field("nblikes", string),
      isliked: json |> field("isliked", string),
    };

  let decodeItemList = json =>
    json |> Json.Decode.(list(optional(decodeItem)));

  let getResults = (query, uti) =>
    Js.Promise.(
      Fetch.fetch(
        "http://127.0.0.1:8080/message?cours=" ++ query ++ "&userId=" ++ uti,
      )
      |> then_(Fetch.Response.json)
      |> then_(json => decodeItemList(json) |> resolve)
      |> then_(results =>
           results  /* Turn our items out of option types into a regular record */
           |> List.map(item =>
                switch (item) {
                | Some(item) => item
                | None => {
                    idmessage: "nada",
                    texte: "",
                    dateenvoi: "",
                    idcours: "",
                    auteur: "",
                    nblikes: "",
                    isliked: "",
                  }
                }
              )
           |> resolve
         )
    );
};

let reducer = (action, state) =>
  switch (action) {
  | UpdateInput(newInput, second) =>
    ReasonReact.Update({...state, input: newInput, utilisateur: second})
  | UpdateText(newText) => ReasonReact.Update({...state, text: newText})
  | UpdateResults(results) =>
    ReasonReact.Update({...state, isLoading: false, results})
  | Search =>
    ReasonReact.UpdateWithSideEffects(
      {...state, isLoading: false},
      (
        self => {
          let value = self.state.input;
          let uti = self.state.utilisateur;
          let _ =
            Api.getResults(value, uti)
            |> Js.Promise.then_(results => {
                 self.send(UpdateResults(results));
                 Js.Promise.resolve();
               });
          ();
        }
      ),
    )
   | _ => ReasonReact.Update({...state, isLoading: false});
  };
