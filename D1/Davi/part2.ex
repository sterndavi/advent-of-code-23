defmodule Day1 do



  def step1(input) do
    {:ok, output} = File.read(input)

    output
    |> String.split(["\n", "\r", "\r\n"])
  end

  def stringreplacer(string, dict) do
    Enum.reduce(dict, string, fn {key, value}, acc ->
      String.replace(acc, key, value)
    end)
  end

  def step2(input, dict_conflict, dict) do
    input
    |> stringreplacer(dict_conflict)
    |> stringreplacer(dict)
  end

  def step3(input) do
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

dict = %{
  "one"   => "1",
  "two"   => "2",
  "three" => "3",
  "four"  => "4",
  "five"  => "5",
  "six"   => "6",
  "seven" => "7",
  "eight" => "8",
  "nine"  => "9",
}

conflicts_dict = %{
  "twone"     => "21",
  "oneight"   => "18",
  "eightwo"   => "82",
  "eightree"  => "83",
  "fiveight"  => "58",
  "nineight"  => "98",
  "threeight" => "38"
}

      list_of_lines = Day1.step1("input.txt")

      list_of_lines
      |> Enum.map(fn x -> Day1.step2(x, conflicts_dict, dict) end)
      |> Day1.step3()
      |> Enum.map(&Day1.first_and_last/1)
      |> Enum.reduce(0, &(&1 + &2))
      |> IO.inspect()
