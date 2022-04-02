#include <iostream>
#include <vector>
#include <string>

class Cube
{
    public:
        Cube(int length, std::string color)
        {
            length_ = length;
            color_ = color;
        };

        ~Cube()
        {
        };

        int getLength()
        {
            return length_;
        };

        friend std::ostream& operator<<(std::ostream &os, const Cube &cube)
        {
            os << cube.length_;
            return os;
        };

    private:
        int length_;
        std::string color_;
};

class Stack{
    public:
        Stack()
        {
        };
        ~Stack()
        {
        };
        
        void push_back(Cube cube)
        {
            cubes_.push_back(cube);
        };

        Cube removeTop()
        {
            Cube removed = cubes_[cubes_.size() - 1];
            cubes_.erase(cubes_.end() - 1);
            return removed;
        };
        Cube & peekTop()
        {
            Cube & peek = cubes_[cubes_.size() - 1];
            return peek;
        };
        unsigned size() const
        {
            return cubes_.size();
        };

        friend std::ostream& operator<<(std::ostream &os, const Stack &stack)
        {
            for (int i = 0; i < stack.cubes_.size(); i++)
            {
                os << stack.cubes_[i] << " ";
            }
            return os;
        };

    private:
        std::vector<Cube> cubes_;
};

class Game{
    public:
        Game(int number_of_cubes)
        {
            number_of_cubes_ = number_of_cubes;
            number_of_steps_ = 0;

            // Create stacks
            for (int i = 0; i < 3; i++)
            {
                Stack stackOfCubes;
                stacks_.push_back(stackOfCubes);
            }

            for (int i = 0; i < number_of_cubes; i++)
            {
                Cube tmp_cube(number_of_cubes - i, std::string("a" + i));
                stacks_[0].push_back(tmp_cube);
            }
        };
        ~Game()
        {
            std::cout << "Number of steps: " << number_of_steps_ << std::endl;
        };

        void legalMove(int index_01, int index_02)
        {
            if (stacks_[index_01].size() > 0 && stacks_[index_02].size() > 0)
            {
                if (stacks_[index_01].peekTop().getLength() < stacks_[index_02].peekTop().getLength())
                {
                    stacks_[index_02].push_back(stacks_[index_01].removeTop());
                }
                else
                {
                    stacks_[index_01].push_back(stacks_[index_02].removeTop());
                }
            }
            else
            {
                if (stacks_[index_01].size() > 0)
                {
                    stacks_[index_02].push_back(stacks_[index_01].removeTop());
                }
                else if (stacks_[index_02].size() > 0)
                {
                    stacks_[index_01].push_back(stacks_[index_02].removeTop());
                }
            }
        }

        void solve_01()
        {
            while (stacks_[2].size() != number_of_cubes_)
            {
                legalMove(0, 1);
                std::cout << *this << std::endl;
                legalMove(0, 2);
                std::cout << *this << std::endl;
                legalMove(1, 2);
                std::cout << *this << std::endl;
                number_of_steps_ += 3;
            }
        };

        void solve_02(int num_of_cubes, int current, int staging, int target)
        {
            if (num_of_cubes == 1)
            {
                stacks_[target].push_back(stacks_[current].removeTop());
                std::cout << *this << std::endl;
                number_of_steps_ += 1;
                return;
            }

            // Top cubes block move to staging
            solve_02(num_of_cubes-1, current, target, staging);  

            // Bottom cube move to target
            solve_02(1, current, staging, target);

            // Top cubes block move to target
            solve_02(num_of_cubes-1, staging, current, target);
        };


        friend std::ostream& operator<<(std::ostream &os, const Game &game)
        {
            for (int i = 0; i < game.stacks_.size(); i++)
            {
                os << "Stack[" << i << "]: " << game.stacks_[i] << std::endl;
            }
            return os;
        };

    private:
        std::vector<Stack> stacks_;
        int number_of_cubes_;
        int number_of_steps_;
};

