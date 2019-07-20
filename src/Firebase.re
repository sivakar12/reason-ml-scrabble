open SharedTypes;

type firebaseConfig = {
    .
    "apiKey": string,
    "databaseURL": string
};

type firebaseDatabase;
type firebaseReference;

let config =  [%bs.obj {
    "apiKey": " AIzaSyBi-KlDUGdM4SlTFJkKMlLi5qGPBWuABvU ",
    "databaseURL": "https://scrabble-e05f2.firebaseio.com/"
}];

[@bs.module "firebase/app"] external initializeApp: (firebaseConfig => unit) = "initializeApp";
[@bs.module "firebase"] external getDatabaseReference: ( unit => firebaseDatabase) = "database";
[@bs.send] external getFirebaseReference: (firebaseDatabase, string) => firebaseReference = "ref";
[@bs.send] external setStringValue: (firebaseReference, string) => Js.Promise.t(unit) = "set";

let startFirebase = () => {
    Js.log("Starting firebase");
    initializeApp(config);
};

let createGame: string => unit = gameId => {
    let database = getDatabaseReference();
    let reference = getFirebaseReference(database, gameId ++ "/playerOneStatus");
    let _ = setStringValue(reference, "joined");
    ()
};

let joinGame: string => unit = gameId => {
    let database = getDatabaseReference();
    let reference = getFirebaseReference(database, gameId ++ "/playerTwoStatus");
    let _ = setStringValue(reference, "joined")
};

let mapConnectionToPath: connection => string = connection => {
    let (gameId, playerId) = connection;
    gameId ++ "/" ++ playerId;
};

let putNewMove: (dataToSend, connection) => Js.Promise.t(unit) = (_dataToSend, connection) => {
    let database = getDatabaseReference();
    let reference = getFirebaseReference(database, mapConnectionToPath(connection) ++ "/data");
    setStringValue(reference, "newMoves")
}