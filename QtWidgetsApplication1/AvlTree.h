#pragma once
class AvlTree
{
public:
	int number_nodes;
	void* root;

	AvlTree() {
		this->number_nodes = 0;
		this->root = nullptr;
	}
};

/*
    +0      +4      +8      +12       +16
|  **** |  ****  | **** |   ****   |  ****  |
| *лево | *право | ключ | значение | высота |

20 байт
*/