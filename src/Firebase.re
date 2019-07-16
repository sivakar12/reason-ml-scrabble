
let createGame: string => unit = [%bs.raw {|
    function(gameId, playerId) {
        console.log(`Creating game ${gameId}`);
    } 
|}]

let joinGame: string => unit = [%bs.raw {|
    function(gameId, playerId) {
        console.log(`Joining game ${gameId}`);
    }
|}]