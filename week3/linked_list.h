#pragma once

template <typename T>
class LinkedList {
public:
	struct Node {
		T value;
		Node* next = nullptr;
	};

	~LinkedList();

	void PushFront(const T& value);
	void InsertAfter(Node* node, const T& value);
	void RemoveAfter(Node* node);
	void PopFront();

	Node* GetHead() { return head; }
	const Node* GetHead() const { return head; }

private:
	Node* head = nullptr;
};

template <typename T>
LinkedList<T>::~LinkedList() {
	while(head != nullptr) {
		PopFront();
	}
}

template <typename T>
void LinkedList<T>::PushFront(const T& value) {
	Node* node = new Node;
	node->value = value;
	node->next = head;
	head = node;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& value) {
	if(node == nullptr) {
		PushFront(value);
		return;
	}

	Node* new_node = new Node;
	new_node->value = value;
	new_node->next = node->next;
	node->next = new_node;
}

template <typename T>
void LinkedList<T>::RemoveAfter(Node* node) {
	if(node == nullptr) {
		PopFront();
		return;
	}

	if(node->next != nullptr) {
		Node* to_remove = node->next;
		node->next = node->next->next;
		delete to_remove;
	}
}

template <typename T>
void LinkedList<T>::PopFront() {
	if(head != nullptr) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}