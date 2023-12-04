using MyNamespace;

void Run()
{
    var lines = FileReader.ReadLines("Day3.txt");

    var lineDetails = lines
        .Select((line, index) =>
        {
            List<Gear> gears = [];
            List<LineNumber> lineNumbers = [];
            string currNumber = "";

            for (int i = 0; i < line.Length; i++)
            {
                var currChar = line[i];

                if (currChar == '*')
                {
                    gears.Add(new Gear(i, []));
                }

                if (!char.IsNumber(currChar))
                {
                    if (currNumber != "")
                    {
                        lineNumbers.Add(new LineNumber(int.Parse(currNumber), i - currNumber.Length, i));
                        currNumber = "";
                    }
                }
                else
                {
                    currNumber += currChar;
                }
            }

            if (currNumber != "")
            {
                lineNumbers.Add(new LineNumber(int.Parse(currNumber), line.Length - currNumber.Length, line.Length));
            }



            return new LineDetails(line, index, index == 0, index == lines.Length - 1, lineNumbers, gears);
        })
        .ToList();

    lineDetails.ForEach(ld => ld.Numbers.ForEach(ln => ln.CheckSurrounding(ld, lineDetails)));

    var part1Res = lineDetails.SelectMany(ld =>
    {
        return ld.Numbers.Where(ldn => ldn.SymbolSurrounded);
    }).Sum(x => x.Number);

    var part2Res = lineDetails
        .SelectMany(ld => ld.Gears)
        .Where(x => x.Numbers.Count == 2)
        .Select(x => x.Numbers.Aggregate((a, b) => a * b))
        .Sum();


    Console.WriteLine(part1Res);
    Console.WriteLine(part2Res);
}

namespace MyNamespace
{
    

public static


internal record LineDetails(string Line, int Index, bool IsTop, bool IsBottom, List<LineNumber> Numbers, List<Gear> Gears);

internal class LineNumber()
{
    public int Number { get; init; }
    public int StartIndex { get; init; }
    public int EndIndex { get; init; }
    public bool SymbolSurrounded { get; set; }


    readonly Func<char, bool> _isSymbol = (char c) => (!char.IsNumber(c) && c != '.');
    readonly Func<char, bool> _isGear = (char c) => (c == '*');

    public LineNumber(int number, int startIndex, int endIndex, bool symbolSurrounded = false) : this()
    {
        Number = number;
        StartIndex = startIndex;
        EndIndex = endIndex;
        SymbolSurrounded = symbolSurrounded;
    }

    public void CheckSurrounding(LineDetails ld, List<LineDetails> allLines)
    {
        bool addedTopAlready = false;
        bool addedBottomAlready = false;
        for (int i = StartIndex; i < EndIndex; i++)
        {
            if (!ld.IsTop)
            {
                var lineDescriptionAbove = allLines[ld.Index - 1];

                var upperleftIndex = i > 0 ? i - 1 : -1;
                var upperRightIndex = i < ld.Line.Length - 1 ? i + 1 : -1;

                if (upperleftIndex > 0)
                {
                    if (_isGear(lineDescriptionAbove.Line[upperleftIndex]) && !addedTopAlready)
                    {
                        lineDescriptionAbove.Gears.First(x => x.Index == upperleftIndex).Numbers.Add(Number);
                        addedTopAlready = true;
                    }
                    if (!SymbolSurrounded && _isSymbol(lineDescriptionAbove.Line[upperleftIndex])) this.SymbolSurrounded = true;
                }


                if (_isGear(lineDescriptionAbove.Line[i]) && !addedTopAlready)
                {
                    lineDescriptionAbove.Gears.First(x => x.Index == i).Numbers.Add(Number);
                    addedTopAlready = true;
                }
                if (!SymbolSurrounded && _isSymbol(lineDescriptionAbove.Line[i])) this.SymbolSurrounded = true;

                if (upperRightIndex > 0)
                {
                    if (_isGear(lineDescriptionAbove.Line[upperRightIndex]) && !addedTopAlready)
                    {
                        lineDescriptionAbove.Gears.First(x => x.Index == upperRightIndex).Numbers.Add(Number);
                        addedTopAlready = true;
                    }
                    if (!SymbolSurrounded && _isSymbol(lineDescriptionAbove.Line[upperRightIndex])) this.SymbolSurrounded = true;
                }

            }

            if (!ld.IsBottom)
            {
                var lineDescriptionBelow = allLines[ld.Index + 1];

                var lowerleftIndex = i > 0 ? i - 1 : -1;
                var lowerRightIndex = i < ld.Line.Length - 1 ? i + 1 : -1;

                if (lowerleftIndex > 0)
                {
                    if (_isGear(lineDescriptionBelow.Line[lowerleftIndex]) && !addedBottomAlready)
                    {
                        lineDescriptionBelow.Gears.First(x => x.Index == lowerleftIndex).Numbers.Add(Number);
                        addedBottomAlready = true;
                    }
                    if (!SymbolSurrounded && _isSymbol(lineDescriptionBelow.Line[lowerleftIndex])) this.SymbolSurrounded = true;
                }

                if (_isGear(lineDescriptionBelow.Line[i]) && !addedBottomAlready)
                {
                    lineDescriptionBelow.Gears.First(x => x.Index == i).Numbers.Add(Number);
                    addedBottomAlready = true;
                }
                if (!SymbolSurrounded && _isSymbol(lineDescriptionBelow.Line[i])) this.SymbolSurrounded = true;


                if (lowerRightIndex > 0)
                {
                    if (_isGear(lineDescriptionBelow.Line[lowerRightIndex]) && !addedBottomAlready)
                    {
                        lineDescriptionBelow.Gears.First(x => x.Index == lowerRightIndex).Numbers.Add(Number);
                        addedBottomAlready = true;
                    }
                    if (!SymbolSurrounded && _isSymbol(lineDescriptionBelow.Line[lowerRightIndex])) this.SymbolSurrounded = true;
                }
            }

            if (i > 0)
            {
                if (_isGear(ld.Line[i - 1])) ld.Gears.First(x => x.Index == i - 1).Numbers.Add(Number);
                if (!SymbolSurrounded && _isSymbol(ld.Line[i - 1])) this.SymbolSurrounded = true;
            }

            if (i < ld.Line.Length - 1)
            {
                if (_isGear(ld.Line[i + 1])) ld.Gears.First(x => x.Index == i + 1).Numbers.Add(Number);
                if (!SymbolSurrounded && _isSymbol(ld.Line[i + 1])) this.SymbolSurrounded = true;
            }
        }


    }
}

internal record Gear(int Index, List<int> Numbers);
}