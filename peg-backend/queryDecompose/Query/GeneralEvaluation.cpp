/*=============================================================================
# Filename: GeneralEvaluation.cpp
# Author: Jiaqi, Chen
# Mail: chenjiaqi93@163.com
# Last Modified: 2016-09-12
# Description: implement functions in GeneralEvaluation.h
=============================================================================*/

#include "GeneralEvaluation.h"



bool GeneralEvaluation::parseGetQuery(const string &_query, int& var_num, QueryTree::QueryForm& query_form, int& star_tag)
{  
    //获取sparql语句
    try
    {
        this->query_parser.SPARQLParse(_query, this->query_tree);
    }
    catch(const char* e)
    {
        cerr << e << endl;
        return false;
    }
    cout<< "打印树" <<std::endl;
    query_tree.print();
    cout << "测试答应：" << std::endl;
    
    this->query_tree.getGroupPattern().print(10);
   //varset为 grouppattren中的参数量。
    this->query_tree.getGroupPattern().getVarset();
    var_num = this->query_tree.getGroupPattern().grouppattern_subject_object_maximal_varset.varset.size();
    cout << var_num << std::endl;


    if(this->query_tree.getQueryForm() == QueryTree::Ask_Query){
        query_form = QueryTree::Ask_Query;
    }else{
        query_form = QueryTree::Select_Query;
    }
    cout <<"quert_form:" <<std::endl; 
    cout << query_form << std::endl;

    
    std::vector<std::vector<std::vector<QueryTree::Vertex>>> queryVertex=this->query_tree.getStarQuery();

    for(int i=0;i<queryVertex.size();i++){
        queriesDecomposed.push_back(query_tree.getSparql(queryVertex[i]));
    }
    
    return true;
}

