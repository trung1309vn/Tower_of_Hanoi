#include "TowerOfHanoi.hpp"

int main()
{
    int number_of_cubes = -1;
    while (number_of_cubes <= 0)
    {
        std::cout << "Enter number of cubes in the tower (must be larger than 0): ";
        std::cin >> number_of_cubes;
    }

    int solution_choice = -1;
    while (solution_choice != 1 && solution_choice != 2)
    {
        std::cout << "Solution choice (1 or 2 only): ";
        std::cin >> solution_choice;
    }

    Game game(number_of_cubes);
    std::cout << "Start\n" << game << std::endl;
    
    if (solution_choice == 1)
        game.solve_01();
    else
        game.solve_02(number_of_cubes, 0, 1, 2);
    
    std::cout << "End\n" << game;
    return 0;
}