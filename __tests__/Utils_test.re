open Jest;

describe("split", () => {
    open Expect;
    test("works on char list", () => {
        let input = ['a', 'b', 'c', ',', 'd', 'e', ',', 'f'];
        let output = [['a', 'b', 'c'], ['d', 'e'], ['f']];
        expect(Utils.split(',', input)) |> toEqual(output)
    })

    test("works on integer list", () => {
        let input = [1, 2, 3, 0, 2, 4, 0, 1, 4, 5];
        let output = [[1, 2, 3], [2, 4], [1, 4, 5]];
        expect(Utils.split(0, input)) |> toEqual(output)
    })

    test("works with multiple spaces", () => {
        let input = [1, 2, 3, 0, 0, 2, 4, 0, 1, 4, 5];
        let output = [[1, 2, 3], [2, 4], [1, 4, 5]];
        expect(Utils.split(0, input)) |> toEqual(output)
    })
})


describe("any", () => {
    open Expect;
    test("works for true", () => {
        let nums = [1, 2, 3];
        let is_even = (x: int) => x == 2;
        expect(Utils.any(is_even, nums)) |> toEqual(true)
    })
    test("works for false", () => {
        let nums = [1, 5, 3];
        let is_even = (x: int) => x == 2;
        expect(Utils.any(is_even, nums)) |> toEqual(false)
    })
})

