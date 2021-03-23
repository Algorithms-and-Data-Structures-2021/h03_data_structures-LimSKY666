#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

void LinkedDequeue::Enqueue(Element e) {

    if (size_ == 0) {
        auto *node = new DoublyNode(e, back_, nullptr);
        front_= node;
        back_ = front_;
    }
    if (size_ > 0) {
        auto *node = new DoublyNode(e, back_, nullptr);
        back_->next = node;
        back_ = node;
    }
    size_++;

}

void LinkedDequeue::EnqueueFront(Element e) {
    if (size_ == 0) {
        auto *node = new DoublyNode(e, nullptr, nullptr);
        front_= node;
        back_ = node;
    }
    if (size_ > 0) {
        auto *node = new DoublyNode(e, nullptr, front_);
        front_->previous = node;
        front_ = node;
    }
    size_++;
}

void LinkedDequeue::Dequeue() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }
    if (size_ == 1) {
//        delete front_;
        front_ = nullptr;
        back_ = nullptr;
        size_--;
    }

    if (size_ > 1) {
        front_ = front_->next;
        front_->previous = nullptr;
//        delete old_node;
        size_--;
    }
}

void LinkedDequeue::DequeueBack() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }
    if (size_ == 1) {
//        delete front_;
        front_ = nullptr;
        back_ = nullptr;
        size_--;
    }

    if (size_ > 1) {

        back_ = back_->previous;
        back_->next = nullptr;
//        delete old_node;
        size_--;
    }
}

void LinkedDequeue::Clear() {
    DoublyNode *current_node = front_;
    while (current_node != nullptr) {
        DoublyNode *nextNode = current_node->next;
        delete current_node;
        front_= nextNode;
        current_node = front_;
        size_ --;
    }
    back_ = nullptr;
}

// === РЕАЛИЗОВАНО ===

LinkedDequeue::~LinkedDequeue() {
  Clear();
}

std::optional<Element> LinkedDequeue::front() const {
  return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
}

std::optional<Element> LinkedDequeue::back() const {
  return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
}

bool LinkedDequeue::IsEmpty() const {
  return size_ == 0;
}

int LinkedDequeue::size() const {
  return size_;
}

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
  os << "size: " << queue.size_ << '\n';
  for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
    if (current_node == queue.front_) os << "[FRONT] ";
    if (current_node == queue.back_) os << "[BACK] ";
    os << enum2str(current_node->data) << '\n';
  }
  return os;
}

}  // namespace itis
