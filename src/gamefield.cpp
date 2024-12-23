#include "gamefield.h"


void GameField::init_field() {
    field = (Cell**) malloc(sizeof (Cell*) * rows);
    for (int i = 0; i < rows; i++){
        field[i] = (Cell*) malloc(sizeof (Cell) * cols);
        for (int j = 0; j < cols; j++){
            field[i][j] = Cell();
        }   
    }
}

GameField::GameField(int rows, int cols) : rows(rows), cols(cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Field dimensions must be positive.");
    }
    init_field();
}

void GameField::placeShip(Ship &ship, Coordinate coords, bool isHorizontal) {
    int length = ship.get_length();
    int segment_index = 0;
    int row = coords.x;
    int col = coords.y;
    if ((isHorizontal && coords.y + length > cols) || (!isHorizontal && coords.x + length > rows)) {
        throw InvalidShipPlacementException("Ship placement out of bounds.");
    }
    for (int i = 0; i < length; i++) {
        if (checkCell(Coordinate{row, col})) {
            throw InvalidShipPlacementException("Ship overlaps with another ship.");
        }
        if (checkAdjacentCells(Coordinate{row, col})){
            throw InvalidShipPlacementException("Ship is adjacent to another ship");
        }
        if (isHorizontal) col++;
        else row++;
    }
    row = coords.x;
    col = coords.y;
        for (int i = 0; i < length; i++) {
        field[row][col].set_segment(ship.get_segment(segment_index));
        segment_index++;
        if (isHorizontal) col++;
        else row++;
    }

}

void GameField::attackCell(Coordinate coords) {
    if (coords.x < 0 || coords.x >= rows || coords.y < 0 || coords.y >= cols) {
        throw OutOfBoundsException("Attack coordinates out of bounds.");
    }

    if (field[coords.x][coords.y].get_segment() != (ShipSegment*) nullptr) {
        field[coords.x][coords.y].set_status(CellStatus::ShipFound);
        field[coords.x][coords.y].get_segment()->takeDamage();
    }
    else {
        field[coords.x][coords.y].set_status(CellStatus::Empty);
    }
}

void GameField::printField() const {
    for (int i = 0; i < rows; i++) {
        std::cout << "|";
        for (int j = 0; j < cols; j++) {
            switch (field[i][j].get_status()) {
            case CellStatus::Unknown:
                std::cout << "?" << "|";
                break;
            case CellStatus::Empty:
                std::cout << "~" << "|";
                break;
            case CellStatus::ShipFound:
                switch (field[i][j].get_segment()->get_status()){
                    case SegmentStatus::Intact:{
                        std::cout << "2" << "|";
                        break;
                    }
                    case SegmentStatus::Damaged: {
                        std::cout << "1" << "|";
                        break;
                    }
                    case SegmentStatus::Destroyed: {
                        std::cout << "0" << "|";
                        break;
                    }
                }
                break;
            }
        }
        std::cout << std::endl;
        for (int i = 0; i < cols*2+1; i++) std::cout << "-";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void GameField::revealField() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (checkCell({i,j})){
                field[i][j].set_status(ShipFound);
            }
            else{
                field[i][j].set_status(Empty);
            }
        }
    } 
}

bool GameField::checkCell(Coordinate target) const {
    return (field[target.x][target.y].get_segment() != (ShipSegment*) nullptr);
}

bool GameField::checkAdjacentCells(Coordinate target) const{
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            Coordinate coords = {target.x + i, target.y + j};
            if (validCoords(coords)){
                if (checkCell(coords))
                    return true;
            }
        }
    }
    return false;
}

bool GameField::validCoords(Coordinate coords) const {
    return (coords.x >= 0 && coords.x < rows && coords.y >= 0 && coords.y < cols);
}

int GameField::get_cols() const {
    return cols;
}

int GameField::get_rows() const {
    return rows;
}

void GameField::deepCopy(const GameField& other) {
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            this->field[i][j].set_status(other.field[i][j].get_status());
            this->field[i][j].set_segment(other.field[i][j].get_segment());
        }
    }   
}

GameField::GameField(const GameField& other){
    if (this != &other){
        this->rows = other.rows;
        this->cols = other.cols;
        init_field();
        this->deepCopy(other);
    }
}
    
GameField& GameField::operator=(const GameField& other){
    if (this != &other){
        this->rows = other.rows;
        this->cols = other.cols;
        this->deepCopy(other);
    }
    return *this;
}
    
void GameField::swap(GameField& other){
    std::swap(rows, other.rows);
    std::swap(cols, other.cols);
    std::swap(field, other.field);
}

GameField::GameField(GameField&& other){
    if (this != &other)
        this->swap(other);
}
    
GameField& GameField::operator=(GameField&& other){
    if (this != &other)
        this->swap(other);
    return *this;
}