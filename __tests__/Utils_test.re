open Jest;

describe("Utils", () => {
    open Expect;
    test("works on char list", () => {
        let input = ['a', 'b', 'c', ',', 'd', 'e', ',', 'f'];
        let output = [['a', 'b', 'c'], ['d', 'e'], ['f']];
        expect(Utils.split(input, ',')) |> toEqual(output)
    })

    test("works on integer list", () => {
        let input = [1, 2, 3, 0, 2, 4, 0, 1, 4, 5];
        let output = [[1, 2, 3], [2, 4], [1, 4, 5]];
        expect(Utils.split(input, 0)) |> toEqual(output)
    })
})

