#pragma once
struct Node {
	//check for end node
	bool is_end;
	//array to the next alphabet
	struct Node* nextAlpha[26];
};
