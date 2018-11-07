[@bs.module] external gql: ReasonApolloTypes.gql = "graphql-tag";

module SearchItems = [%graphql
  {|
  query searchItems($queryParam: String!, $typeParam: String!) {
    search(queryParam: $queryParam, typeParam: $typeParam) {
      ... on Artist {
        type
        id
      }
      ... on Album {
        type
        id
      }
      ... on Playlist {
        id
        type
      }
      ... on Track {
        type
        id
      }
    }
  }
|}
];

module SearchItemsQuery = ReasonApollo.CreateQuery(SearchItems);

let component = ReasonReact.statelessComponent("Results");

let make = (~query, _children) => {
  ...component,
  render: _self => {
    let searchItemsQuery =
      SearchItems.make(
        ~typeParam={|album,artist,playlist,track|},
        ~queryParam=query,
        (),
      );

    <SearchItemsQuery variables=searchItemsQuery##variables>
      ...{
           ({result}) =>
             switch (result) {
             | Loading => <div> {"Loading" |> ReasonReact.string} </div>
             | Error(_e) => <div> {"Error" |> ReasonReact.string} </div>
             | Data(response) =>
               <div style=Styles.searchResult>
                 {
                   switch (response##search) {
                   | None => <div> {"Loading" |> ReasonReact.string} </div>
                   | Some(matches) =>
                     let realMatches =
                       matches->Belt.Array.keepMap(match => match);
                     realMatches->Belt.Array.map(item =>
                       switch (item) {
                       | `Album(_item) =>
                         <div> {"al" |> ReasonReact.string} </div>
                       | `Artist(_item) =>
                         <div> {"ar" |> ReasonReact.string} </div>
                       | `Track(_item) =>
                         <div> {"tr" |> ReasonReact.string} </div>
                       | `Playlist(_item) =>
                         <div> {"pl" |> ReasonReact.string} </div>
                       }
                     )
                     |> ReasonReact.array;
                   }
                 }
               </div>
             }
         }
    </SearchItemsQuery>;
  },
};