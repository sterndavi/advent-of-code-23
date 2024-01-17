defmodule Day1 do
  def step1(input) do
    {:ok, output} = File.read(input)

    output
      |> String.split(["\n", "\r", "\r\n"])
    end

    def step2(input) do
        input
        |> Enum.map(fn x -> String.replace(x, ~r/\D/, "") end)
  end

  def first_and_last(str) do
    case String.graphemes(str) do
      [first | []] ->
        String.to_integer("#{first}#{first}")

      [first | rest] ->
        last = List.last(rest)
        String.to_integer("#{first}#{last}")

      [] ->
        0
    end
  end
end

list_of_lines = Day1.step1("input.txt")

list_of_lines
  |> Day1.step2()
  |> Enum.map(&Day1.first_and_last/1)
  |> Enum.reduce(0, &(&1 + &2))
  |> IO.inspect()
