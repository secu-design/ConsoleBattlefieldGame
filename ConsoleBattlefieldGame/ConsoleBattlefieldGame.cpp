#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <random>
#include <sstream>
using std::cin;
using std::cout;
using std::endl;

constexpr std::size_t GridSize{ 5 };
constexpr std::size_t ShipsNum{ 3 };
const std::string ShipView{ "XX" };
std::size_t Hits{};
std::size_t Turns{};

auto GetRandomNum(const int MIN, const int MAX) {
   std::random_device rd;  // a seed source for the random number engine
   std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
   std::uniform_int_distribution<> distrib(MIN, MAX);
   return distrib(gen);
}

void DrawBattlefield(const std::string grid[][GridSize])
{
   std::ostringstream ostream;

   system("cls");
   ostream
      << ">>> BATTLESHIP <<<\n\n\n"
      << "This is your battlefield. Search and destroy " << ShipsNum << " ships.\n";

   for (std::size_t row{}; row < GridSize; ++row) {
      ostream << '|';
      for (std::size_t col{}; col < GridSize; ++col) {
         ostream << std::setw(2) << grid[row][col] << "|";
      }
      ostream << '\n';
   }

   ostream << "\nHits: " << Hits << " | Turns: " << Turns;
   cout << ostream.str() << endl;
}

bool GetFieldPos(
   const std::string& field_name,
   const std::string grid[][GridSize],
   std::array<char, 2>& field_pos)
{
   for (auto row = 0; row < GridSize; ++row) {
      for (auto col = 0; col < GridSize; ++col) {
         if (field_name == grid[row][col]) {
            field_pos.at(0) = row;
            field_pos.at(1) = col;
            return true;
         }
      }
   }

   return false;
}

void ClearBattlefield(std::string grid[][GridSize]) {
   for (std::size_t row{}; row < GridSize; ++row) {
      for (std::size_t col{}; col < GridSize; ++col) {
         if (grid[row][col] != ShipView)
         {
            grid[row][col].clear();
         }
      }
   }
}

int main()
{
   std::string SelectedField{};
   std::array<char, 2> FieldPos{};
   bool GridData[GridSize][GridSize]{};

   std::string GridView[][GridSize]{
   {"1","2","3","4","5"},
   {"6","7","8","9","10"},
   {"11","12","13","14","15"},
   {"16","17","18","19","20"},
   {"21","22","23","24","25"}
   };

   // Generate ship non-equal ship positions
   std::array<std::string, ShipsNum> ShipPositions{};
   for (std::size_t i = 0; i < ShipsNum; ++i)
   {
      auto RandPos = std::to_string(GetRandomNum(1, GridSize * GridSize));
      while (std::find(ShipPositions.begin(), ShipPositions.end(), RandPos) != ShipPositions.end())
      {
         RandPos = std::to_string(GetRandomNum(1, GridSize * GridSize));
      }
      ShipPositions[i] = RandPos;
   }

   // Place ships on battlefield
   for (const auto& pos : ShipPositions) {
      GetFieldPos(pos, GridView, FieldPos);
      GridData[FieldPos.at(0)][FieldPos.at(1)] = 1;
   }

   while (Hits < ShipsNum)
   {
      DrawBattlefield(GridView);

      cout << "\nChoose a field you want to bomb: " << std::flush;
      std::getline(cin, SelectedField);

      if (GetFieldPos(SelectedField, GridView, FieldPos)) {
         Turns += 1;
         GridView[FieldPos.at(0)][FieldPos.at(1)].clear();
         DrawBattlefield(GridView);

         // A ship was hit
         if (GridData[FieldPos.at(0)][FieldPos.at(1)]) {
            Hits += 1;
            GridView[FieldPos.at(0)][FieldPos.at(1)] = ShipView;
            DrawBattlefield(GridView);

            GridData[FieldPos.at(0)][FieldPos.at(1)] = 0;

            if (Hits < ShipsNum)
            {
               cout << "\nBoom, you hit a ship!" << endl;
               system("pause");
            }
         }
      }
   }

   ClearBattlefield(GridView);
   DrawBattlefield(GridView);
   cout << "\nCongratulation, you hit all ships." << endl;
   system("pause");
}