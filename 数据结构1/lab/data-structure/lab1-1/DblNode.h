//
// Created by 邱姜铭 on 2023/11/29.
//

#ifndef DATA_STRUCTURE_DBLNODE_H
#define DATA_STRUCTURE_DBLNODE_H


template<class ElemType>
struct DblNode {
    ElemType data;
    DblNode<ElemType> *prior;
    DblNode<ElemType> *next;

    DblNode();

    DblNode(ElemType e,
            DblNode<ElemType> *priorlink = nullptr,
            DblNode<ElemType> *nextlink = nullptr);
};

template<class ElemType>
DblNode<ElemType>::DblNode() {
    prior = nullptr;
    next = nullptr;
}

template<class ElemType>
DblNode<ElemType>::DblNode(ElemType e,
                           DblNode<ElemType> *priorlink,
                           DblNode<ElemType> *nextlink)
{
    data=e;
    prior=priorlink;
    next=nextlink;
}


#endif //DATA_STRUCTURE_DBLNODE_H
