#pragma once

#include <iostream>
#include <string>

using namespace std::string_view_literals;

class IdentityDocument {
public:
	IdentityDocument()
	: unique_id_(++unique_id_count_) {
		IdentityDocument::SetVTable(this);
		std::cout << "IdentityDocument::Ctor() : "sv << unique_id_ << std::endl;
	}
	~IdentityDocument() {
		--unique_id_count_;
		std::cout << "IdentityDocument::Dtor() : "sv << unique_id_ << std::endl;
	}
	IdentityDocument(const IdentityDocument& other)
	: unique_id_(++unique_id_count_) {
		IdentityDocument::SetVTable(this);
		std::cout << "IdentityDocument::CCtor() : "sv << unique_id_ << std::endl;
	}

	IdentityDocument& operator = (const IdentityDocument&) = delete;

	static void SetVTable(IdentityDocument* obj) {
		*(IdentityDocument::Vtable**)obj = &IdentityDocument::VTABLE;
	}

	using PrintIDFunction = void(*)(const IdentityDocument*);
	using DeleteFunction = void(*)(IdentityDocument*);

	struct Vtable {		
		DeleteFunction delete_this;
		PrintIDFunction print_id_this;
	};	

	void PrintID() const {
		vptr_->print_id_this(this);
	}

	void Delete() {
		vptr_->delete_this(this);
	}
	
	const Vtable* GetVtable() const {
		return vptr_;
	}

	Vtable* GetVtable() {
		return vptr_;
	}

	static void PrintUniqueIDCount() {
		std::cout << "unique_id_count_ : "sv << unique_id_count_ << std::endl;
	}

	int GetID() const {
		return unique_id_;
	}

private:	
	
	//! на первом месте указатель на таблицу
	IdentityDocument::Vtable* vptr_= nullptr; //указатель на таблицу
	static IdentityDocument::Vtable VTABLE; //сама таблица
	
	static void Delete(IdentityDocument* obj) {
		delete obj;
	}

	static void PrintID(const IdentityDocument* obj) {
		std::cout << "IdentityDocument::PrintID : "sv << obj->unique_id_ << std::endl;
	}

	int unique_id_;
	static int unique_id_count_;
};

//определяем саму таблицу и записываем в нее методы
IdentityDocument::Vtable IdentityDocument::VTABLE = { 
	IdentityDocument::Delete, IdentityDocument::PrintID };

int IdentityDocument::unique_id_count_ = 0;
