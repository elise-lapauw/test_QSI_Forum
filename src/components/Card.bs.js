// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as Fetch from "bs-fetch/src/Fetch.js";
import * as React from "react";
import * as Caml_format from "bs-platform/lib/es6/caml_format.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as ReasonReact from "reason-react/src/ReasonReact.js";
import * as UpJpg from "../img/up.jpg";
import * as DownPng from "../img/down.png";
import * as LikeJpg from "../img/like.jpg";
import * as UserPng from "../img/user.png";
import * as TrashJpg from "../img/trash.jpg";

var logo = UserPng.default;

var logo2 = LikeJpg.default;

var logo3 = TrashJpg.default;

var up = UpJpg.default;

var down = DownPng.default;

var component = ReasonReact.statelessComponent("Card");

var message = {
  border: "1px solid grey",
  clear: "right",
  float: "right",
  marginTop: "10px",
  marginRight: "5%",
  overflow: "hidden",
  padding: "10px",
  size: "200px",
  width: "430px",
  borderRadius: "8px"
};

var pied = {
  clear: "left",
  float: "left",
  fontSize: "12px",
  marginLeft: "5%"
};

var img = {
  clear: "left",
  float: "left",
  marginRight: "3%",
  width: "50px",
  clipPath: "ellipse(50% 50%)"
};

var img2 = {
  clear: "right",
  float: "right",
  marginRight: "3%",
  width: "50px",
  clipPath: "ellipse(50% 50%)"
};

var container = {
  clear: "right",
  color: "black",
  float: "right",
  position: "relative",
  textAlign: "center",
  width: "50px",
  clipPath: "ellipse(50% 50%)"
};

var centered = {
  fontSize: "15px",
  fontWeight: "bold",
  left: "50%",
  position: "absolute",
  top: "50%",
  transform: "translate(-50%, -50%)"
};

var trash = {
  clear: "right",
  float: "right",
  marginRight: "3%",
  width: "30px",
  clipPath: "ellipse(50% 50%)"
};

function make(idmessage, texte, dateenvoi, idcours, auteur, nblikes, isliked, appSend, utilisateur, _children) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (_self) {
              return React.createElement("div", {
                          style: message
                        }, React.createElement("img", {
                              style: img,
                              alt: "",
                              src: logo
                            }), React.createElement("div", {
                              style: container
                            }, React.createElement("img", {
                                  style: img2,
                                  alt: "",
                                  src: logo2
                                }), React.createElement("div", {
                                  style: centered
                                }, nblikes)), texte, React.createElement("br", undefined), isliked === "0" ? React.createElement("img", {
                                style: trash,
                                alt: "",
                                src: up,
                                onClick: (function (ev) {
                                    var payload = { };
                                    payload["idMessage"] = Caml_format.caml_int_of_string(idmessage);
                                    payload["userId"] = utilisateur;
                                    fetch("http://127.0.0.1:8080/like", Fetch.RequestInit.make(/* Post */2, {
                                                  "Content-Type": "application/json"
                                                }, Caml_option.some(JSON.stringify(payload)), undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined)(/* () */0)).then((function (prim) {
                                            return prim.json();
                                          }));
                                    return Curry._1(appSend, /* Search */1);
                                  })
                              }) : React.createElement("img", {
                                style: trash,
                                alt: "",
                                src: down,
                                onClick: (function (ev) {
                                    var payload = { };
                                    payload["idMessage"] = Caml_format.caml_int_of_string(idmessage);
                                    payload["userId"] = utilisateur;
                                    fetch("http://127.0.0.1:8080/like", Fetch.RequestInit.make(/* Delete */4, {
                                                  "Content-Type": "application/json"
                                                }, Caml_option.some(JSON.stringify(payload)), undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined)(/* () */0)).then((function (prim) {
                                            return prim.json();
                                          }));
                                    return Curry._1(appSend, /* Search */1);
                                  })
                              }), auteur === utilisateur ? React.createElement("img", {
                                style: trash,
                                alt: "",
                                src: logo3,
                                onClick: (function (ev) {
                                    var payload = { };
                                    payload["idMessage"] = Caml_format.caml_int_of_string(idmessage);
                                    fetch("http://127.0.0.1:8080/message", Fetch.RequestInit.make(/* Delete */4, {
                                                  "Content-Type": "application/json"
                                                }, Caml_option.some(JSON.stringify(payload)), undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined)(/* () */0)).then((function (prim) {
                                            return prim.json();
                                          }));
                                    return Curry._1(appSend, /* Search */1);
                                  })
                              }) : null, React.createElement("br", undefined), React.createElement("span", {
                              style: pied
                            }, "Message de: " + (auteur + (" le: " + dateenvoi))));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

export {
  logo ,
  logo2 ,
  logo3 ,
  up ,
  down ,
  component ,
  message ,
  pied ,
  img ,
  img2 ,
  container ,
  centered ,
  trash ,
  make ,
  
}
/* logo Not a pure module */