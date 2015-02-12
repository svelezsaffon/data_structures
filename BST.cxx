/*
 * BST.cxx
 * 
 * Copyright 2015 Santiago <santiago@santiago-XPS>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <cstdio>
#include <vector>

template<class T>
class _BST_TREE_NODE{

private:	
	T value;	
	_BST_TREE_NODE *left;
	_BST_TREE_NODE *right;
	
public:	
	_BST_TREE_NODE(){
		this->left=0x0;
		this->right=0x0;
	};
	
	int is_left_null(){
		return this->left==0x0;
	};
	
	void set_left(_BST_TREE_NODE * ll){
		this->left=ll;
	}
	
	void set_rigt(_BST_TREE_NODE * rr){
		this->right=rr;
	}
	
	
	_BST_TREE_NODE * get_left(){
		return this->left;
	}
	
	_BST_TREE_NODE * get_rigt(){
		return this->right;
	}
	
	int is_right_null(){
		return this->right==0x0;
	};
	
	void set_value(T val){
		this->value=val;
	};
	
	T get_value(){
		return this->value;
	};
	
};

template<class T>
class BST_TREE{

private:	
	_BST_TREE_NODE<T> *root;
	
	void insert(_BST_TREE_NODE<T>*,T,int (BST_TREE::*p)(T,T));
	void insert(_BST_TREE_NODE<T>*,T,int (*p)(T,T));
	
	int T_greater(T a, T b){return a>b;};
	void in_order(_BST_TREE_NODE<T>*,std::vector<T> &);
public:
	
	BST_TREE(T);
	
	void insert(T value,int (*p)(T,T));	
	void insert(T);
	std::vector<T> in_order();	
	
};


template<class T>
BST_TREE<T>::BST_TREE(T rooo){
	this->root=new _BST_TREE_NODE<T>();
	this->root->set_value(rooo);
};



/*INSERT FUNCTION WITH DEFAULT COMPARISON FUNCTION*/
template<class T>
void BST_TREE<T>::insert(_BST_TREE_NODE<T> *nodel,T val,int (BST_TREE::*_P_)(T,T)){
		if((this->*_P_)(val,nodel->get_value())){
		
			if(nodel->is_right_null()){
					_BST_TREE_NODE<T> *nodea=new _BST_TREE_NODE<T>();
					nodea->set_value(val);
					nodel->set_rigt(nodea);
			}else{
				BST_TREE::insert(nodel->get_rigt(),val,_P_);				
			}		
			
	}else{

			if(nodel->is_left_null()){
					_BST_TREE_NODE<T> *nodea=new _BST_TREE_NODE<T>();
					nodea->set_value(val);
					nodel->set_left(nodea);
			}else{
				BST_TREE::insert(nodel->get_left(),val,_P_);				
			}
		
	}
};

template<class T>
void BST_TREE<T>::insert(T val){	
	int (BST_TREE::*aux)(T,T);	
	aux=&BST_TREE::T_greater;	
	insert(this->root,val,aux);
};



/*INSERT FUNCTION WITH POINTER TO COMPARISON FUNCTION*/
template<class T>
void BST_TREE<T>::insert(_BST_TREE_NODE<T> *nodel,T val,int (*_P_)(T,T)){
	
	if(_P_(val,nodel->get_value())){
		
			if(nodel->is_right_null()){
					_BST_TREE_NODE<T> *nodea=new _BST_TREE_NODE<T>();
					nodea->set_value(val);
					nodel->set_rigt(nodea);
			}else{
				BST_TREE::insert(nodel->get_rigt(),val,_P_);				
			}		
			
	}else{
			if(nodel->is_left_null()){
					_BST_TREE_NODE<T> *nodea=new _BST_TREE_NODE<T>();
					nodea->set_value(val);
					nodel->set_left(nodea);
			}else{
				BST_TREE::insert(nodel->get_left(),val,_P_);				
			}
	}
};

template<class T>
void BST_TREE<T>::insert(T val,int (*_P_)(T,T)){		
	insert(this->root,val,_P_);
};


template<class T>
void BST_TREE<T>::in_order(_BST_TREE_NODE<T> *current,std::vector<T> &res){
	if(!current->is_left_null()){
		BST_TREE::in_order(current->get_left(),res);
	}	
		res.push_back(current->get_value());
	
	if(!current->is_right_null()){
		BST_TREE::in_order(current->get_rigt(),res);
	}
	
	
};

template<class T>
std::vector<T> BST_TREE<T>::in_order(){
	std::vector<T> res;
	BST_TREE::in_order(this->root,res);
	
	return res;
};


int greater(int a, int b){
	return a>b;
};


int main(int argc, char **argv)
{
	BST_TREE<int> tree(3);
	tree.insert(1,&greater);
	tree.insert(2,&greater);
	tree.insert(4);
	tree.insert(5,&greater);
	
	std::vector<int>aux=tree.in_order();
	
	
	std::vector<int>::iterator i=aux.begin();
	
	for(;i!=aux.end();i++){
		printf("%d ",(*i));
	}
	
	
	
	return 0;
}
