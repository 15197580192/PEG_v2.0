#include "joiner.h"

void joiner::addItem(string item, vector<string> &elements)
{
    if (hashTable.find(item) == hashTable.end())
        hashTable[item] = vector<string>();
    for (vector<string>::const_iterator it = elements.begin(); it != elements.end(); it++)
        hashTable[item].push_back(*it);
}

bool joiner::isContained(string item)
{
    return hashTable.find(item) != hashTable.end();
}

void joiner::split(const string &s, vector<string> &tokens, string delimiters)
{
    string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    string::size_type pos = s.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.push_back(s.substr(lastPos, pos - lastPos)); // use emplace_back after C++11
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
}

long long joiner::getFinalResNum()
{
    return this->finalResNum;
}

// Calculate intersection var cnt
// 将s1,s2中相等的值放进comonVar
vector<string> joiner::intersection(const vector<string> &s1, const vector<string> &s2)
{
    vector<string> commonVar;
    for (auto it1 : s1)
        for (auto it2 : s2)
            if (it1 == it2)
                commonVar.push_back(it1);

    return commonVar;
}

// Union 2 vector by STL set
vector<string> joiner::unionSet(const vector<string> &s1, const vector<string> &s2)
{
    set<string> varSet;
    for (auto it1 : s1)
        varSet.insert(it1);
    for (auto it2 : s2)
        varSet.insert(it2);

    return vector<string>(varSet.begin(), varSet.end());
}

/**
 * 输入和输出都是按行划分后的
 */
vector<string> joiner::join(vector<string> &res1, vector<string> &res2, nlohmann::json &dataans)
{
    cout << "================== Joining res1 and res2 ==================" << endl;
    cout << "Size of res1 is: " << res1.size() << endl;
    cout << "Size of res2 is: " << res2.size() << endl;
    cout << "================== Joining res1 and res2 ==================" << endl;

    vector<string> ans; // 返回的结果
    if (res1.size() == 0 || res2.size() == 0)
        return ans;
    vector<string> varVec_1;
    vector<string> varVec_2;

    split(res1[0], varVec_1, "\t"); // 头部？
    split(res2[0], varVec_2, "\t");
    map<string, int> varMap_1;
    map<string, int> varMap_2;
    // varMap["?v0"] = 0, varMap["?v2"] = 1, etc.
    cout << "varVec_1:" << endl;
    string head1;
    string head2;
    for (int i = 0; i < varVec_1.size(); i++)
    {
        head1 += varVec_1[i];
        head1 += "\t";
        cout << varVec_1[i] << endl;
    }
    cout << head1 << endl;
    dataans["头部1"] = head1;

    for (int i = 0; i < varVec_2.size(); i++)
    {
        head2 += varVec_2[i];
        head2 += "\t";
        cout << varVec_2[i] << endl;
    }
    cout << head2 << endl;
    dataans["头部2"] = head2;
    for (int i = 0; i < varVec_1.size(); i++)
    {
        varMap_1[varVec_1[i]] = i; // 将每个头部都放进map并且对应一个Int值。
    }

    for (int i = 0; i < varVec_2.size(); i++)
        varMap_2[varVec_2[i]] = i;

    // build vec on the basis of larger one, by grouping the smaller one
    bool choose = res1.size() < res2.size();
    vector<string> *buildVec = choose ? &res2 : &res1; // 谁大取谁
    map<string, int> *buildVarMap = choose ? &varMap_2 : &varMap_1;
    vector<string> *probeVec = choose ? &res1 : &res2; // 谁小取谁
    map<string, int> *probeVarMap = choose ? &varMap_1 : &varMap_2;

    cout << "buildVarMap's size is " << buildVarMap->size() << endl;
    for (auto &it : *buildVarMap)
        cout << it.first << " ";
    cout << endl;
    cout << "probeVarMap's size is " << probeVarMap->size() << endl;
    for (auto &it : *probeVarMap)
        cout << it.first << " ";
    cout << endl;

    // 建hash表
    hashTable.clear();
    vector<string> intersectionVar = intersection(varVec_1, varVec_2); // 相同头部拼起来
    string xdtb;
    cout << "intersectionVar:" << endl;
    for (int i = 0; i < intersectionVar.size(); i++)
    {
        xdtb += intersectionVar[i];
        xdtb += "\t";
        cout << intersectionVar[i] << endl;
    }
    dataans["相等头部"] = xdtb;
    cout << "intersectionVar Num: " << intersectionVar.size() << endl;
    if (intersectionVar.size() == 0) // 两个查询结果头部没有相同项
    {
        string t = "Intersection Error";
        return vector<string>(1, t);
    }
    vector<string> elements;
    for (int i = 1; i < buildVec->size(); i++) // 从一开始，拿查询结果的各项。
    {
        elements.clear();
        split(buildVec->at(i), elements, "\t"); // 将一行结果的各项放入element
        string elements_in_line = "";
        for (vector<string>::iterator it = intersectionVar.begin(); it != intersectionVar.end(); it++)
            elements_in_line += elements.at((*buildVarMap)[*it]); // 将相同项放入element
        addItem(elements_in_line, elements);                      // element数据放入hash表 ，hash 表前索引为对应头部的答案的拼接，后索引为实际结果。
    }

    // 查hash表，还需要把变量和结果做并操作
    string vars = "";
    vector<string> varsVec = unionSet(varVec_1, varVec_2); // union 的作用是拼接在一起并且去重 , 这里应该是获得多项 如 ?X ?y 和 ?X ?y ?Z 获得 ?x ?y ?Z
    vars += varsVec[0];
    for (int i = 1; i < varsVec.size(); i++)
        vars += ("\t" + varsVec[i]); // 获得所有头部。
    ans.push_back(vars);             // 插入ans。

    for (int i = 1; i < probeVec->size(); i++) // 小项
    {
        elements.clear();
        split(probeVec->at(i), elements, "\t");
        string elements_in_line = "";
        for (vector<string>::iterator it = intersectionVar.begin(); it != intersectionVar.end(); it++)
            elements_in_line += elements.at((*probeVarMap)[*it]); // 获得对应头部的拼接。
        if (isContained(elements_in_line))                        // 遍历哈希
        {
            for (int j = 0; j < hashTable[elements_in_line].size(); j += buildVarMap->size()) // 遍历一条结果。
            {
                string oneLineOfAns = "";
                for (int k = 0; k < varsVec.size(); k++) // 对于任何一个头部的参数遍历
                {
                    if (probeVarMap->find(varsVec[k]) != probeVarMap->end())
                        oneLineOfAns += elements[probeVarMap->at(varsVec[k])]; // 获得对应头部的结果。
                    else
                        oneLineOfAns += hashTable[elements_in_line][j + buildVarMap->at(varsVec[k])]; // 再拿另一个表对应头部的结果。
                    if (k < varsVec.size() - 1)
                        oneLineOfAns += "\t";
                }
                ans.push_back(oneLineOfAns);
            }
        }
    }
    cout << "After joining, ans num is " << ans.size() << endl;
    return ans;
}

// arg results[0] : "<v1>\t<v2>\t<v3> \n <v1>\t<v3>\t<v2> \n ..."
vector<string> joiner::join(queue<vector<string> *> &results, nlohmann::json &dataans, int &joinnum)
{

    // if partial has no results or arg:results is empty, return ""
    if (results.empty())
        return vector<string>();

    for (int i = 0; i < results.size(); ++i)
    {
        if (results.front()->size() != 0)
            break;
        results.push(results.front());
        results.pop();
        if (i == results.size() - 1)
            return vector<string>();
    }
    // 第一个result
    vector<string> linesOfAns0 = *results.front();
    results.pop();
    int num = 0;
    while (!results.empty())
    {
        vector<string> linesOfAnsi = *results.front();
        // cout << "ans1:" << endl;
        // for (int i = 0; i < linesOfAns0.size(); i++)
        // {
        //     cout << linesOfAns0[i] << endl;
        // }
        // cout << "ans2:" << endl;
        // for (int i = 0; i < linesOfAnsi.size(); i++)
        // {
        //     cout << linesOfAnsi[i] << endl;
        // }
        nlohmann::json tmpjson;
        vector<string> joinRes = join(linesOfAns0, linesOfAnsi, tmpjson);
        dataans[num] = tmpjson;
        num++;

        if (joinRes.size() > 0 && joinRes[0].compare("Intersection Error") == 0)
        {
            results.push(results.front());
        }
        else
        {
            linesOfAns0 = joinRes;
        }
        results.pop();
        joinnum++;
    }

    if (linesOfAns0.size() == 0 || linesOfAns0.size() == 1)
    {
        return vector<string>();
    }
    else
    // 输出第一个查询结果的长度
    {
        cout << "There has answer: " << linesOfAns0.size() - 1 << endl;
        return linesOfAns0;
    }
}

string joiner::join(string &res1, string &res2, nlohmann::json &dataans)
{
    vector<string> lines_1;
    vector<string> lines_2;

    split(res1, lines_1, "\n");
    split(res2, lines_2, "\n");

    vector<string> ans = join(lines_1, lines_2, dataans);

    string finalRes;

    for (auto item : ans)
    {
        finalRes += item;
        finalRes += "\n";
    }

    return finalRes;
}

string joiner::Union(string &res1, string &res2)
{
    bool res1b = res1.compare("[empty result]") == 0;
    bool res2b = res2.compare("[empty result]") == 0;
    if (res1b && res2b)
        return "[empty result]";
    else if (res1b && !res2b)
        return res2;
    else if (!res1b && res2b)
        return res1;

    set<string> s;
    string head = res1.substr(0, res1.find_first_of("\n"));
    // cout << "head is : " << head << endl;
    res1 = res1.substr(res1.find_first_of("\n") + 1);
    res2 = res2.substr(res2.find_first_of("\n") + 1);

    vector<string> v1, v2;
    split(res1, v1, "\n");
    split(res2, v2, "\n");

    for (auto it : v1)
        s.insert(it);
    for (auto it : v2)
        s.insert(it);

    string finalRes = head + "\n";
    finalResNum += s.size();
    for (auto it : s)
    {
        finalRes += it;
        finalRes += "\n";
    }
    return finalRes;
}

vector<string> joiner::Union(vector<string> &res1, vector<string> &res2)
{
    bool res1b = res1.size() == 0 || res1.size() == 1;
    bool res2b = res2.size() == 0 || res2.size() == 1;

    if (res1b && res2b)
        return vector<string>();
    else if (res1b && !res2b)
        return res2;
    else if (!res1b && res2b)
        return res1;

    set<string> s;
    vector<string> res;
    res.push_back(*res1.begin()); // head

    for (auto it = res1.begin() + 1; it != res1.end(); it++)
        s.insert(*it);
    for (auto it = res2.begin() + 1; it != res2.end(); it++)
        s.insert(*it);

    res.insert(res.end(), s.begin(), s.end());

    return res;
}