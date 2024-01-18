#include<iostream>
#include<ctime>
#include<cstring>
#include<climits>

using namespace std;

enum Type {
	WALL, BLANK
};

struct Position {
	int x, y;

	Position() : x(0), y(0) {}
	Position(int x, int y) : x(x), y(y) {}
	Position operator+(const Position& other) const {
		return Position(x + other.x, y + other.y);
	}
	bool operator==(const Position& other) const {
		return x == other.x && y == other.y;
	}
};

const Position DIRECTIONS[4] = { Position(-1,0), Position(0,1), Position(1,0), Position(0,-1) };

int mapX;
int mapY;

Type **map; 

#define blockWall "■"
#define blockRoad "□"
#define blockWay "☆"

inline bool isValid(const Position& pos)
{
	return pos.x >= 0 && pos.x < mapX &&
		pos.y >= 0 && pos.y < mapY;
}


inline bool isWall(const Position& pos)
{
	return isValid(pos) && map[pos.x][pos.y] == WALL;
}

inline bool isRoad(const Position& pos)
{
	return isValid(pos) && map[pos.x][pos.y] == BLANK;
}

inline bool isUnreachable(const Position& pos)
{
	return !isValid(pos) || map[pos.x][pos.y] == WALL;
}

void printMap(Position* path = nullptr, int pathLength = 0)
{
	auto isInPath = [&](int x, int y) -> bool {
		for (int i = 0; i < pathLength; ++i) {
			if (path[i].x == x && path[i].y == y)
				return true;
		}
		return false;
	};

	// Upper border
	printf(blockWall);
	for (int j = 0; j < mapY; ++j)
		printf(blockWall);
	printf(blockWall "\n");

	// Middle rows
	for (int i = 0; i < mapX; ++i) {
		printf((i == 0 ? blockWay : blockWall));
		for (int j = 0; j < mapY; ++j) {
			if (path && isInPath(i, j))
				printf(blockWay);
			else
				printf("%2s", (map[i][j] == WALL ? blockWall : blockRoad));
		}
		printf((i == mapX - 1 ? blockWay : blockWall));
		printf("\n");
	}

	// Lower border
	printf(blockWall);
	for (int j = 0; j < mapY; ++j)
		printf(blockWall);
	printf(blockWall "\n");
}

void initMap(Type type = WALL)
{
	for (int i = 0; i < mapX; ++i)
		for (int j = 0; j < mapY; ++j)
			map[i][j] = type;
}

void generateMap(Position seed)
{
	if (seed.x <= 0 || seed.x >= mapX - 1) seed.x = 1;
	if (seed.y <= 0 || seed.y >= mapY - 1) seed.y = 1;

	const int initialSize = 10;
	Position* stack = new Position[initialSize];
	int stackSize = 0;
	int stackCapacity = initialSize;

	auto push = [&](const Position& pos) {
		if (stackSize == stackCapacity) {
			stackCapacity *= 2;
			Position* newStack = new Position[stackCapacity];
			memcpy(newStack, stack, stackSize * sizeof(Position));
			delete[] stack;
			stack = newStack;
		}
		stack[stackSize++] = pos;
	};

	auto popRandom = [&]() -> Position {
		int randomIndex = rand() % stackSize; // 随机选择一个索引
		Position chosen = stack[randomIndex];
		stack[randomIndex] = stack[stackSize - 1]; // 将选择的元素与栈顶元素交换
		stackSize--; // 减少栈大小
		return chosen;
	};

	auto isEmpty = [&]() -> bool {
		return stackSize == 0;
	};

	auto isOnStack = [&](const Position& pos) -> bool {
		for (int i = 0; i < stackSize; ++i) {
			if (stack[i] == pos) {
				return true;
			}
		}
		return false;
	};

	push(seed);
	initMap(); // 初始化整个地图为墙

	while (!isEmpty()) {
		Position current = popRandom(); // 随机选择一个元素

		int roadCount = 0;
		for (int i = 0; i < 4; i++) {
			Position nextPlace = current + DIRECTIONS[i];
			if (isRoad(nextPlace)) {
				roadCount++;
			}
		}

		// 如果当前位置周围的道路不超过1条，创建新道路
		if (roadCount <= 1) {
			map[current.x][current.y] = BLANK;
			for (int i = 0; i < 4; i++) {
				Position nextPlace = current + DIRECTIONS[i];
				if (isWall(nextPlace) && !isOnStack(nextPlace) && isValid(nextPlace)) {
					push(nextPlace);
				}
			}
		}
	}

	if(map[0][0]!=BLANK)
		map[0][0] = BLANK;
	if(map[mapX-1][mapY-1]!=BLANK)
		map[mapX-1][mapY-1] = BLANK;

	delete[] stack; // 清理栈
}

struct Path {
	Position* positions;
	int length;
	int capacity;

	Path(int cap) : length(0), capacity(cap) {
		positions = new Position[capacity];
	}

	~Path() {
		delete[] positions;
	}

	void push_back(const Position& pos) {
		if (length == capacity) {
			capacity *= 2;
			Position* newPositions = new Position[capacity];
			memcpy(newPositions, positions, length * sizeof(Position));
			delete[] positions;
			positions = newPositions;
		}
		positions[length++] = pos;
	}

	void pop_back() {
		if (length > 0) {
			length--;
		}
	}

	Position& back() const {
		return positions[length - 1];
	}

	bool contains(const Position& pos) const {
		for (int i = 0; i < length; ++i) {
			if (positions[i] == pos) {
				return true;
			}
		}
		return false;
	}
};

bool dfs(const Position& current, const Position& destination, Path& path, bool** visited) {
	if (!isValid(current) || isWall(current) || visited[current.x][current.y]) {
		return false;
	}
	visited[current.x][current.y] = true;
	path.push_back(current);

	if (current == destination) {
		return true;
	}

	for (int i = 0; i < 4; ++i) {
		Position next = current + DIRECTIONS[i];
		if (dfs(next, destination, path, visited)) {
			return true;
		}
	}

	path.pop_back();
	return false;
}

Path findPath(const Position& start, const Position& end, int mapX, int mapY) {
	Path path(10);
	bool** visited = new bool* [mapX];
	for (int i = 0; i < mapX; ++i) {
		visited[i] = new bool[mapY];
		memset(visited[i], 0, mapY * sizeof(bool));
	}

	if (dfs(start, end, path, visited)) {
		cout << "找到路径：";
		for (int i = 0; i < path.length; ++i) {
			cout << "(" << path.positions[i].x << ", " << path.positions[i].y << ") ";
			if (i < path.length - 1) {
				cout << "-> ";
			}
		}
		cout << endl;

	}
	else {
		cout << "No path found." << endl;
	}

	for (int i = 0; i < mapX; ++i) {
		delete[] visited[i];
	}
	delete[] visited;

	return path;
}

int main()
{
	srand((unsigned int)(time(NULL)));
	while (1) {
		cout << "请输入地图的行数和列数, 以空格分隔: ";
		cin >> mapX >> mapY;
		if (cin.fail())
			printf("输入有误\n");
		else if (mapX <= 0)
			printf("行数有误\n");
		else if (mapY <= 0)
			printf("列数有误\n");
		else if (mapX > 100)
			printf("行数过大\n");
		else if (mapY > 100)
			printf("列数过大\n");
		else
			break;
		cin.clear();
		cin.ignore(INT_MAX, '\n'); 
	}
	cout << "迷宫大小：" << mapX << "行 " << mapY << "列" << endl;
	map = new Type*[mapX];
	for (int i = 0; i < mapX; ++i)
		map[i] = new Type[mapY];
	generateMap(Position(0, 0));
	cout << endl;
	printMap();

	Path path = findPath(Position(0, 0), Position(mapX - 1, mapY - 1), mapX, mapY);

	printMap(path.positions, path.length); 

	system("pause");

	return 0;
}

