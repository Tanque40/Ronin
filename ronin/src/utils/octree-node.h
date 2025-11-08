#pragma once

#include "roninpch.h"

template<typename T>
class OctreeNode {
private:
	T data;
	std::array<OctreeNode<T>*, 8> children;

public:
	OctreeNode(T _data) : data(_data), children() {}
	~OctreeNode() {
		for (auto child : children) {
			delete child;
		}
	}


};
