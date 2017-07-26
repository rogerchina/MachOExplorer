//
// Created by everettjf on 2017/7/23.
//

#include "FatHeaderViewNode.h"

MOEX_NAMESPACE_BEGIN
void FatHeaderViewNode::Init(FatHeaderPtr d){
    d_ = d;
    for(auto & f : d_->archs()){
        MachHeaderViewNodePtr node = std::make_shared<MachHeaderViewNode>();
        node->Init(f->mh());
        headers_.push_back(node);
    }
}

void FatHeaderViewNode::ForEachChild(std::function<void(ViewNode*)> callback){
    for(auto & h : headers_){
        callback(h.get());
    }
}


std::vector<ViewData*> FatHeaderViewNode::GetViewDatas(){
    using namespace moex::util;

    // Table
    if(vd_table_.get() == nullptr){
        vd_table_ = std::make_shared<TableViewData>();
        vd_table_->SetHeaders({"Offset","Data","Description","Value"});

        const fat_header * h = d_->offset();

        vd_table_->AddRow({
                AsAddress(d_->GetRAW(&(h->magic))),
                AsHexData(h->magic),
                "Magic Number",
                GetMagicString(h->magic),
                          });

        vd_table_->AddRow({
                  AsAddress(d_->GetRAW(&(h->nfat_arch))),
                  AsHexData(h->nfat_arch),
                  "Number of Architecture",
                  AsString(d_->data().nfat_arch),
                          });
    }

    if(vd_binary_.get() == nullptr){

    }

    return {vd_table_.get()};
}

MOEX_NAMESPACE_END
