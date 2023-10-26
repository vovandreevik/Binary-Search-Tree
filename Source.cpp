#include <iostream>
#include "BinarySearchTree.h"

int main() {
	std::cout << "test 1\n";
	BinarySearchTree<int> test;
	for (int i = 0; i < 10; i++) {
		test.insert(rand() % 20);
	}
	test.print(std::cout);

	std::cout << "Count: " << test.getCount() << std::endl;
	std::cout << "Height: " << test.getHeight() << std::endl;

	std::cout << "iterative inorder walk: ";
	test.inorderWalk();
	std::cout << std::endl << "inorder walk: ";
	test.inorderWalk();
	std::cout << std::endl << "walk by levels: ";
	test.walkByLevels();

	std::cout << std::endl << std::endl << "Test 2\n";
	BinarySearchTree<int> test1;
	test1.insert(4);
	test1.insert(2);
	test1.insert(6);
	test1.insert(1);
	test1.print(std::cout);

	std::cout << "Is 4 in tree: " << test1.iterativeSearch(4)<< std::endl;
	std::cout << "Is 9 in tree: " << test1.iterativeSearch(9) << std::endl;

	std::cout << "Let's add 6 " << test1.insert(6) << std::endl;

	std::cout << "Let's delete 6 " << test1.deleteKey(6) << std::endl;
	std::cout << "Let's delete 6 " << test1.deleteKey(6) << std::endl;
	std::cout << "Is 6 in tree: " << test1.iterativeSearch(6) << std::endl << std::endl;
	test1.insert(6);

	std::cout << "Test 3\n";
	BinarySearchTree<int> test2;
	test2.insert(4);
	test2.insert(2);
	test2.insert(6);
	test2.insert(1);
	test2.print(std::cout);

	std::cout << "are similar tree 2 and tree 3: " << test2.isSimilar(test1);
	std::cout << std::endl << "are identical keys in tree 2 and tree 3: " << test2.isIdenticalKey(test1) << std::endl;

	std::cout << "Let's add 15 in tree 3 " << test2.insert(15) << std::endl;

	std::cout << "are similar tree 2 and tree 3: " << test2.isSimilar(test1);
	std::cout << std::endl << "are identical keys in tree 2 and tree 3: " << test2.isIdenticalKey(test1) << std::endl;

	test.~BinarySearchTree();
	test1.~BinarySearchTree();
	test2.~BinarySearchTree();
	return 0;
}