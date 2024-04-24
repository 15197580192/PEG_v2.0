#include "database.h"
// 构造函数
database::Database::Database()
{
    database_id_ = "0";
    database_name_ = "0";
    creater_id_ = "0";
    database_password_ = "0";
    database_version_ = "0";
}
/*****************************************************************
 * 函数名称： void database::Database::NewDatabase(std::string database_id,std::string database_name,
 *                                                std::string creater_id,std::string database_password,
 *                                                std::string database_version)
 * 功能描述： 赋予数据库类数据
 * 参数说明： 字符串类型的数据库id,数据库名字，创建者id,数据库密码，数据库版本
 * 返回值：   符合要求的数据库列表
 ******************************************************************/
void database::Database::NewDatabase(std::string database_id, std::string database_name, std::string creater_id, 
                                     std::string database_password, std::string database_version)
{
    this->set_creater_id_(creater_id);
    this->set_database_id_(database_id);
    this->set_database_name_(database_name);
    this->set_database_password_(database_password);
    this->set_database_version_(database_version);
}

/*****************************************************************
 * 函数名称： std::vector<Database *> UserQueryDB(std::vector<Database *> db_list, const std::string &creater_id)
 * 功能描述： 得到该用户id下的所有数据库
 * 参数说明： 字符串，输入的创造者id；vector，为数据库列表
 * 返回值：   符合要求的数据库列表
 ******************************************************************/
std::vector<database::Database *> database::UserQueryDb(std::vector<database::Database *> db_list,
                                                        const std::string &creater_id)
{
    std::vector<database::Database *> database_id;
    for (auto it = db_list.begin(); it != db_list.end(); it++)
    {
        if ((*it)->get_creater_id_() == creater_id)
        {
            database_id.push_back(*it);
        }
    }
    return database_id;
}

/*****************************************************************
 * 函数名称： Database * DatabaseIdGetData(const std::string &database_id, std::vector<Database *> db_list)
 * 功能描述： 根据数据库id获得该数据库信息
 * 参数说明： 字符串，输入的数据库id；vector，为数据库列表
 * 返回值：   符合要求的数据库对象
 ******************************************************************/
database::Database *database::DatabaseIdGetData(const std::string &database_id, 
                                                std::vector<database::Database *> db_list)
{
    for (int i = 0; i < db_list.size(); i++)
    {
        if (db_list[i]->get_database_id_() == database_id)
        {
            return db_list[i];
        }
    }
}

// 根据数据库名称和创建者id获得数据库id
/*****************************************************************
 * 函数名称： std::string GetDatabaseId(const std::string &database_name, const std::string &database_creater_id,
 *                                     std::vector<Database *> db_list)
 * 功能描述： 根据数据库名称和创建者id获得数据库id
 * 参数说明： 字符串，输入的数据库名称和创建者；vector，为数据库列表
 * 返回值：   符合要求的数据库id
 ******************************************************************/
std::string database::GetDatabaseId(const std::string &database_name, const std::string &database_creater_id,
                                    std::vector<database::Database *> db_list)
{
    for (int i = 0; i < db_list.size(); i++)
    {
        if (db_list[i]->get_creater_id_() == database_creater_id && db_list[i]->get_database_name_() == database_name)
        {
            return db_list[i]->get_database_id_();
        }
    }
    return "failed";
}

/*****************************************************************
 * 函数名称： std::string GetDatabasePassword(const std::string &database_name, 
 *                                           const std::string &database_creater_id,
 *                                           std::vector<Database *> db_list)
 * 功能描述： 根据数据库名称和创建者id获得数据库密码
 * 参数说明： 字符串，输入的数据库名称和创建者；vector，为数据库列表
 * 返回值：   符合要求的数据库密码
 ******************************************************************/
std::string database::GetDatabasePassword(const std::string &database_name, const std::string &database_creater_id,
                                          std::vector<database::Database *> db_list)
{
    for (int i = 0; i < db_list.size(); i++)
    {
        if (db_list[i]->get_creater_id_() == database_creater_id && db_list[i]->get_database_name_() == database_name)
        {
            return db_list[i]->get_database_password_();
        }
    }
    return "failed";
}
/*****************************************************************
 * 函数名称： database::Database::DbExport(std::vector<GstoreConnector *> &servers, const std::string &path)
 * 功能描述： 数据库导出
 * 参数说明： 节点列表，地址
 * 返回值：   符合要求的数据库密码
 ******************************************************************/
std::string database::Database::DbExport(std::vector<GstoreConnector *> &servers, const std::string &path)
{
    int part = servers.size();
    ExportThreadArgs build_threads_args[part];
    pthread_t export_pthrds[part];
    for (int i = 0; i < part; i++)
    {

        build_threads_args[i].server_ = servers[i];
        build_threads_args[i].db_name_ = this->get_database_id_();
        build_threads_args[i].path_ = path;
        if (pthread_create(&export_pthrds[i], NULL, ExportThread, &build_threads_args[i]) != 0)
            throw runtime_error("creates export thread error!");
    }
    for (int i = 0; i < part; i++)
        pthread_join(export_pthrds[i], NULL);

    for (int i = 0; i < part; i++)
    {

        if (build_threads_args[i].res_.find("successfully") != std::string::npos)
        {
            return build_threads_args[i].res_;
        }
    }

    return "fail";
}
/*****************************************************************
 * 函数名称： database::Database::DbExport(std::vector<GstoreConnector *> &servers, const std::string &path)
 * 功能描述： 数据库增
 * 参数说明： 节点列表，增的sql语句
 * 返回值：   执行语句的信息
 ******************************************************************/
nlohmann::json database::Database::DbInsert(std::vector<GstoreConnector *> &servers, std::string insert_sql)
{
    nlohmann::json data_ans;
    int part = servers.size();
    data_ans["节点个数"] = to_string(part + 1);
    // 加载database
    BuildThreadArgs build_threads_args[part];
    pthread_t load_pthrds[part];
    for (int i = 0; i < part; i++)
    {
        build_threads_args[i].server_ = servers[i];
        build_threads_args[i].db_name_ = this->get_database_id_();
        if (pthread_create(&load_pthrds[i], NULL, LoadThread, &build_threads_args[i]) != 0)
        {
            throw runtime_error("creates load thread error!");
        }
    }
    for (int i = 0; i < part; i++)
        pthread_join(load_pthrds[i], NULL);

    // insert 语句
    data_ans["插入语句"] = insert_sql;
    string isincurrpart = "<http://property/isInCurrPart>";
    // 拆出主宾语
    int index1 = insert_sql.find("<");
    int index2 = insert_sql.find(">", index1);
    string subject(insert_sql, index1, index2 - index1 + 1);
    index1 = insert_sql.find_last_of("<");
    index2 = insert_sql.find_last_of(">");
    string object(insert_sql, index1, index2 - index1 + 1);
    // 拼接查询语句，查询该点是否存在
    data_ans["主语"] = subject;
    data_ans["宾语"] = object;
    string sbuject_sql = "select  ?z where \n {\n" + subject + "\t<http://property/isInCurrPart>\t?z\n }";
    string object_sql = "select  ?z where \n {\n" + object + "\t<http://property/isInCurrPart>\t?z\n }";
    string check_arr[2];
    check_arr[0] = object_sql;
    check_arr[1] = sbuject_sql;
    // 查询两条语句，一条主语一条宾语
    QNV qnv[2][part];
    std::queue<std::vector<std::string> *> results;
    // 并行查询
    pthread_t thread[2][servers.size()];
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < part; i++)
        {
            qnv[j][i].query_id_ = 0;
            qnv[j][i].server_id_ = i;
            qnv[j][i].server_ = servers[i];
            qnv[j][i].db_name_ = this->get_database_id_();
            qnv[j][i].format_ = "json";
            qnv[j][i].query_ = check_arr[j];
            if (pthread_create(&thread[j][i], NULL, QueryThread, &qnv[j][i]) != 0)
            {
                throw runtime_error("creates thread error!");
            }
        }
    }
    string exist;
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < servers.size(); i++)
            pthread_join(thread[j][i], NULL);
    }
    // 如果主语或宾语不存在，默认插入第一个节点,-1表示不存在，其他数据对应其在的节点。
    int subject_in = -1;
    int object_in = -1;
    // 先找sub
    for (int i = 0; i < part; i++)
    {
        crow::json::rvalue rv = crow::json::load(qnv[1][i].res_);
        crow::json::wvalue twv(rv["results"]["bindings"]);
        string u = twv.dump();
        // 不存在
        if (u == "[]")
        {
            exist += "主语不存在";
            continue;
        }
        else
        {
            u = twv[0]["z"]["value"].dump();
            if (u == "\"1\"")
                subject_in = i;
            exist += "主语存在" + subject_in;
        }
    }
    for (int i = 0; i < part; i++)
    {
        crow::json::rvalue rv = crow::json::load(qnv[0][i].res_);
        crow::json::wvalue twv(rv["results"]["bindings"]);
        string u = twv.dump();
        // 不存在
        if (u == "[]")
        {
            exist += "宾语不存在";
            continue;
        }
        else
        {
            u = twv[0]["z"]["value"].dump();
            if (u == "\"1\"")
                object_in = i;
            exist += "宾语存在" + object_in;
        }
    }
    vector<string> insert_arr;
    // 情况1主语或宾语不存在。
    if (object_in == -1 || subject_in == -1)
    {
        data_ans["插入情况"] = "主语或者宾语不存在";
        return data_ans;
    }
    // 都存在，且在同一个节点,只用添加一个语句

    if (object_in != -1 && subject_in != -1 && object_in == subject_in)
    {
        data_ans["插入情况"] = "主语和宾语在同一节点";
        insert_arr.push_back(to_string(object_in));
        insert_arr.push_back(insert_sql);
    }
    // 都存在，在不同节点，要加三条语句
    if (object_in != -1 && subject_in != -1 && object_in != subject_in)
    {
        data_ans["插入情况"] = "主语和宾语在不同节点";
        insert_arr.push_back(to_string(subject_in));
        insert_arr.push_back(insert_sql);
        insert_arr.push_back(to_string(subject_in));
        string insql2 = "insert data\n{\n" + object + "\t" + isincurrpart + "\t0 .\n}";
        string insql3 = "insert data\n{\n" + subject + "\t" + isincurrpart + "\t1 .\n}";
        insert_arr.push_back(insql2);
        insert_arr.push_back(to_string(object_in));
        insert_arr.push_back(insql3);
    }
    // 执行语句

    int do_num = (insert_arr.size() + 1) / 2;
    QNV qnv2[do_num];
    pthread_t thread1[do_num];
    for (int i = 0; i < insert_arr.size(); i += 2)
    {
        qnv2[i / 2].server_ = servers[stoi(insert_arr[i])];
        qnv2[i / 2].db_name_ = this->get_database_id_();
        qnv2[i / 2].format_ = "json";
        qnv2[i / 2].query_ = insert_arr[i + 1];
        if (pthread_create(&thread1[i], NULL, QueryThread, &qnv2[i / 2]) != 0)
        {
            throw runtime_error("creates thread error!");
        }
    }

    for (int i = 0; i < do_num; i++)
    {
        pthread_join(thread1[i], NULL);
    }

    return data_ans;
}
/*****************************************************************
 * 函数名称： nlohmann::json database::Database::DbDelete(std::vector<GstoreConnector *> &servers, 
 *                                                       std::string delete_sql)
 * 功能描述： 数据库删
 * 参数说明： 节点列表，删的sql语句
 * 返回值：   执行语句的信息
 ******************************************************************/
nlohmann::json database::Database::DbDelete(std::vector<GstoreConnector *> &servers, std::string delete_sql)
{
    nlohmann::json data_ans;
    int part = servers.size();
    data_ans["节点个数"] = to_string(part);
    // 加载database
    BuildThreadArgs build_threads_args[part];
    pthread_t load_pthrds[part];
    for (int i = 0; i < part; i++)
    {

        build_threads_args[i].server_ = servers[i];
        build_threads_args[i].db_name_ = this->get_database_id_();
        if (pthread_create(&load_pthrds[i], NULL, LoadThread, &build_threads_args[i]) != 0)
        {
            throw runtime_error("creates load thread error!");
        }
    }
    for (int i = 0; i < part; i++)
        pthread_join(load_pthrds[i], NULL);
  
    data_ans["删除语句"] = delete_sql;

    QNV qnv[part];
    pthread_t thread[part];

    for (int i = 0; i < part; i++)
    {
        qnv[i].query_id_ = 0;
        qnv[i].server_id_ = i;
        qnv[i].server_ = servers[i];
        qnv[i].db_name_ = this->get_database_id_();
        qnv[i].format_ = "json";
        qnv[i].query_ = delete_sql;
        if (pthread_create(&thread[i], NULL, QueryThread, &qnv[i]) != 0)
        {
            throw runtime_error("creates thread error!");
        }
    }
    for (int i = 0; i < part; i++)
    {
        pthread_join(thread[i], NULL);
    }
    for (int i = 0; i < part; i++)
    {  
        data_ans["结果"][i]["节点"] = "节点" +to_string(i);
        data_ans["结果"][i]["结果"] = qnv[i].res_;
    }
    return data_ans;
}
/*****************************************************************
 * 函数名称： int database::Divide(const std::string &nt_file, const std::string &divide_file)
 * 功能描述： 数据库划分
 * 参数说明： nt文件和划分文件的地址
 * 返回值：   返回需要节点的数量
 ******************************************************************/
int database::Divide(const std::string &nt_file, const std::string &divide_file)
{
    std::ifstream ifs_divide_file;
    ifs_divide_file.open(divide_file);
    int num = 0;
    std::string entity;
    int part_id;
    std::unordered_map<std::string, int> entity_to_id;

    while (ifs_divide_file >> entity && ifs_divide_file >> part_id)
    {
        entity_to_id.insert(std::pair<std::string, int>(entity, part_id));
        num = part_id > num ? part_id : num;
    }
    num++;

    std::ifstream ifs_nt_file;
    ifs_nt_file.open(nt_file);

    std::vector<std::ofstream> outfiles;
    outfiles.resize(num);
    std::string prefix = nt_file.substr(0, nt_file.find_last_of('.'));
    for (int i = 0; i < num; i++)
        outfiles[i].open(prefix + to_string(i) + ".nt");

    std::string line;
    std::vector<std::set<std::string>> s;
    s.resize(num);
    while (getline(ifs_nt_file, line))
    {
        std::string subject;
        std::string predict;
        std::string object;
        int left_index, right_index;

        left_index = line.find_first_of('<');
        right_index = line.find_first_of('>');
        subject = line.substr(left_index, right_index - left_index + 1);

        left_index = line.find_first_of('<', right_index + 1);
        right_index = line.find_first_of('>', right_index + 1);
        predict = line.substr(left_index, right_index - left_index + 1);

        left_index = line.find_first_of('<', right_index + 1);
        right_index = line.find_first_of('>', right_index + 1);

        int subPart_id = entity_to_id[subject];
        outfiles[subPart_id] << line << "\n";
        s[subPart_id].insert(subject + "\t" + "<http://property/isInCurrPart>" + "\t" + "\"1\" .\n");

        if (left_index != std::string::npos)
        {
            object = line.substr(left_index, right_index - left_index + 1);
            if (entity_to_id.find(object) != entity_to_id.end())
            {
                int objpart_id = entity_to_id[object];
                if (subPart_id == objpart_id)
                {
                    s[subPart_id].insert(object + "\t" + "<http://property/isInCurrPart>" + "\t" + "\"1\" .\n");
                }
                else
                {
                    s[subPart_id].insert(object + "\t" + "<http://property/isInCurrPart>" + "\t" + "\"0\" .\n");

                    outfiles[objpart_id] << line << "\n";
                    s[objpart_id].insert(subject + "\t" + "<http://property/isInCurrPart>" + "\t" + "\"0\" .\n");
                    s[objpart_id].insert(object + "\t" + "<http://property/isInCurrPart>" + "\t" + "\"1\" .\n");
                }
            }
        }
    }

    for (int i = 0; i < num; i++)
        for (auto iter = s[i].begin(); iter != s[i].end(); iter++)
            outfiles[i] << *iter << std::endl;

    for (int i = 0; i < num; i++)
        outfiles[i].close();
    ifs_nt_file.close();
    ifs_divide_file.close();

    return num;
};

/*****************************************************************
 * 函数名称： int database::Database::DBBuild(vector<map<string, string>> confJson,
 *                                           std::vector<GstoreConnector *> &servers,
 *                                           const std::string &db_path, const std::string &divfile_path)
 * 功能描述： 创建数据库函数
 * 参数说明： 划分节点，nt文件所在路径，划分路径
 * 返回值：   int值
 ******************************************************************/
int database::Database::DbBuild(std::vector<std::map<std::string, std::string>> confJson,
                                std::vector<GstoreConnector *> &servers,
                                const std::string &db_path, const std::string &divfile_path)
{
    // 数据图划分，得到一些nt文件的路径
    std::string txt_name = db_path;                                      // 源数据图路径
    std::string sign = ("2" == "1") ? " " : "\t";                        // 分隔符
    std::string out_file = db_path.substr(0, db_path.find_last_of('.')); // 输出文件的前缀
    int part = Divide(db_path, divfile_path);
    // 分片分发
    TransferThreadArgs transfer_thread_args[part];
    pthread_t thread[part];
    for (int i = 0; i < part; i++)
    {
        transfer_thread_args[i].file_transfer_ = new FileTransfer(servers[i]->serverIP,"root");
        transfer_thread_args[i].localfile_path_ = out_file + to_string(i) + ".nt";
        transfer_thread_args[i].remotefile_path_ = "/tmp/" + this->get_database_id_() + to_string(i) + ".nt";
        if (pthread_create(&thread[i], NULL, TransferThread, &transfer_thread_args[i]) != 0)
        {
            throw runtime_error("creates transfer thread error!");
        }
    }
    for (int i = 0; i < part; i++)
    {
        pthread_join(thread[i], NULL);
    }
    // TODO 调用gStore http api 建库
    BuildThreadArgs build_threads_args[part];
    pthread_t build_pthrd[part];
    for (int i = 0; i < part; i++)
    {
        build_threads_args[i].server_ = servers[i];
        build_threads_args[i].db_name_ = this->get_database_id_();
        build_threads_args[i].nt_path_ = "/tmp/" + this->get_database_id_() + to_string(i) + ".nt";
        if (pthread_create(&build_pthrd[i], NULL, BuildThread, &build_threads_args[i]) != 0)
        {
            throw runtime_error("creates build thread error!");
        }
    }
    for (int i = 0; i < part; i++)
        pthread_join(build_pthrd[i], NULL);

    for (int i = 0; i < part; i++)
    {
        delete transfer_thread_args[i].file_transfer_;
    }
    return 0;
};
/*****************************************************************
 * 函数名称：nlohmann::json database::Database::DbQuery(std::vector<GstoreConnector *> &servers, std::string query)
 * 功能描述： 查询函数，划分输入的sparql语句，分解查询，组合结果
 * 参数说明： 划分节点，数据库名，sparql语句
 * 返回值：   json值，返回查询结果和过程
 ******************************************************************/
nlohmann::json database::Database::DbQuery(std::vector<GstoreConnector *> &servers, std::string query)
{
    nlohmann::json data;
    int part = servers.size();
    data["节点数目"] = part;
    // load
    BuildThreadArgs build_threads_args[part];
    pthread_t load_pthrds[part];
    int frame_num = 0;
    for (int i = 0; i < query.size(); i++)
    {
        if (query[i] == '\n')
        {
            frame_num++;
        }
    }
    cout<<"frame_name:"<<frame_num<<endl;
    for (int i = 0; i < part; i++)
    {
        build_threads_args[i].server_ = servers[i];
        build_threads_args[i].db_name_ = this->get_database_id_();
        if (pthread_create(&load_pthrds[i], NULL, LoadThread, &build_threads_args[i]) != 0)
        {
            throw runtime_error("creates load thread error!");
        }
    }
    for (int i = 0; i < part; i++)
        pthread_join(load_pthrds[i], NULL);

    // query
    // 查询分解、组合
    std::vector<std::vector<std::string>> total_queries;
    std::vector<std::vector<std::string>>::iterator item2v;
    long query_time = Util::get_cur_time();
    if (frame_num != 3)
    {
        std::string _query_str = query;
        data["查询语句"] = query;
        int PPQueryVertexCount = -1, vec_size = 0, star_tag = 0;
        QueryTree::QueryForm query_form = QueryTree::Ask_Query;
        GeneralEvaluation parser_evaluation;
        parser_evaluation.parseGetQuery(_query_str, PPQueryVertexCount, query_form, star_tag); // 作用
        printf("PPQueryVertexCount = %d\n", PPQueryVertexCount);
        printf("query_form = %d\n", query_form);
        printf("star_tag = %d\n", star_tag);
        // total_queries里面是要分解查询的语句。
        total_queries = parser_evaluation.queriesDecomposed;
        item2v = total_queries.begin();
    }
    if (frame_num == 3)
    {
        vector<string> v1;
        v1.push_back(query);
        total_queries.push_back(v1);
    }
    data["分解次数"] = total_queries.size();
    int check_num = 0;
    for (int i = 0; i < total_queries.size(); i++)
    {
        for (int j = 0; j < total_queries[i].size(); j++)
        {
            check_num++;
        }
    }
    data["分解查询次数"] = check_num;
    long query_divide_time = Util::get_cur_time();
    data["分解语句耗时"] = query_divide_time - query_time;
    // query on each site.
    std::vector<std::vector<std::string>> total_results;
    joiner joinobj;
    std::map<std::string, std::vector<std::string> *> query_to_res;
    int query_cnt = 0; // 查询次数
    for (int k = 0; k < total_queries.size(); k++)
        query_cnt += total_queries[k].size();
    int check_num1 = 0;
    int check_num2 = 0;
    for (int k = 0; k < total_queries.size(); k++)
    {
        long query_begintime = Util::get_cur_time();
        std::vector<std::string> &queries = total_queries[k];
        data["总"][k]["分解次数"] = k;
        // 执行查询
        std::queue<std::vector<std::string> *> results;
        // 并行查询
        pthread_t thread[queries.size()][servers.size()];
        QNV qnv[queries.size()][servers.size()];
        long query_time[servers.size()];
        // vector<long> query_time[servers.size()];
        memset(query_time, 0, sizeof query_time);
        std::set<int> skip_query_num;
        for (int i = 0; i < queries.size(); i++)
        {
            data["总"][k]["查询过程"][i]["查询次数"] = i;
            data["总"][k]["查询过程"][i]["查询语句"] = queries[i];
            if (query_to_res.find(queries[i]) == query_to_res.end()) // 该sql未执行
                for (int j = 0; j < servers.size(); j++)
                {
                    qnv[i][j].query_id_ = i;
                    qnv[i][j].server_id_ = j;
                    qnv[i][j].server_ = servers[j];
                    qnv[i][j].db_name_ = this->get_database_id_();
                    qnv[i][j].format_ = "json";
                    data["总"][k]["查询过程"][i]["查询节点"][j]["节点ip"] = servers[j]->serverIP;
                    data["总"][k]["查询过程"][i]["查询节点"][j]["节点port"] = servers[j]->serverPort;
                    qnv[i][j].query_ = queries[i];
                    if (pthread_create(&thread[i][j], NULL, QueryThread, &qnv[i][j]) != 0)
                    {
                        throw runtime_error("creates thread error!");
                    }
                }
            else // 已经执行
            {
                skip_query_num.insert(i);
            }
        }
        for (int i = 0; i < queries.size(); i++)
        {
            if (skip_query_num.find(i) == skip_query_num.end())
                for (int j = 0; j < servers.size(); j++)
                    pthread_join(thread[i][j], NULL);
        }
        // 合并并行查询后的结果
        for (int i = 0; i < queries.size(); i++)
        {
            if (query_to_res.find(queries[i]) == query_to_res.end())
            {
                bool first_res = true;
                std::set<std::string> s; // 去掉重复的结果
                std::string head;
                for (int j = 0; j < servers.size(); j++)
                {

                    crow::json::rvalue rv = crow::json::load(qnv[i][j].res_);
                    crow::json::wvalue twv(rv["head"]["vars"]);
                    string hv = twv.dump();
                    int indexhv0 = 2;
                    string thv;
                    while (indexhv0 < hv.size())
                    {
                        string hv2(hv, indexhv0, 1);
                        indexhv0 += 4;
                        thv += "?";
                        thv += hv2;
                        thv += "\t";
                    }
                    std::vector<string> tv;
                    string tempres;
                    for (int l = 0; l < rv["results"]["bindings"].size(); l++)
                    {
                        crow::json::wvalue wv(rv["results"]["bindings"][l]);
                        string tmp = "[";
                        tmp += wv.dump();
                        tmp += "]";
                        crow::json::rvalue rv2 = crow::json::load(tmp);
                        crow::json::wvalue wv2(rv2);
                        int index1 = tmp.find("value");
                        int index2 = tmp.find("type", index1);
                        while (index1 != std::string::npos)
                        {
                            string tmp3 = "<";
                            string tmp2(tmp, index1 + 8, index2 - index1 - 11);
                            tmp3 += tmp2;
                            tmp3 += ">";
                            tempres += tmp3;
                            tempres += "\t";
                            index1 = tmp.find("value", index2);
                            index2 = tmp.find("type", index1);
                        }
                        tempres += "\n";
                    }
                    string hb = thv;
                    hb += "\n";
                    hb += tempres;
                    std::string &temp_res = hb;
                    if (temp_res.empty())
                    {
                        continue;
                    }
                    else if (tempres.empty()) // 查出的结果是空集
                    {
                        continue;
                    }
                    std::vector<std::string> lines; // 装的是一行查询结果
                    joiner::split(temp_res, lines, "\n");
                    std::vector<std::string>::iterator iter = lines.begin();
                    // head 是 变量 ?x ?y ?z ...
                    head = *iter;
                    ++iter;
                    if (first_res) // 第一次添加结果 ,不加入变量
                    {
                        first_res = false;
                    }
                    for (; iter != lines.end(); iter++)
                        s.insert(*iter); // 将结果插入s
                }

                std::vector<std::string> *query_res = new std::vector<std::string>; // 是否要new?你问我？
                if (!first_res)                                                     // 有结果   这一步意义是什么。。。
                {
                    // 取变量，然后插入数据
                    query_res->push_back(head);
                    query_res->insert(query_res->end(), s.begin(), s.end());
                }
                results.push(query_res); // 将结果集放入results
                query_to_res[queries[i]] = query_res;
            }
            else
            {
                results.push(query_to_res[queries[i]]);
            }
        }
        // results存的是地址
        data["总"][k]["连接前大小"] = results.size();
        // join
        long joinbegin = Util::get_cur_time();
        nlohmann::json data_ans;
        int join_num = 0;

        std::vector<std::string> final_res = joinobj.join(results, data_ans, join_num); // 只有一条结果的情况下，返回空集
        data["总"][k]["连接次数"] = join_num;
        data["总"][k]["连接过程"] = data_ans;
        long query_endtime = Util::get_cur_time();
        total_results.push_back(final_res);
    }

    // unload
    pthread_t unload_pthrds[part];
    for (int i = 0; i < part; i++)
        if (pthread_create(&unload_pthrds[i], NULL, UnloadThread, &build_threads_args[i]) != 0)
            throw runtime_error("creates unload thread error!");
    for (int i = 0; i < part; i++)
        pthread_join(unload_pthrds[i], NULL);

    // union
    // 作用是 去重？
    long union_begintime = Util::get_cur_time();
    std::vector<std::string> union_res = total_results[0];
    for (int i = 1; i < total_results.size(); i++)
    { // 内定义一个set去重
        union_res = joinobj.Union(union_res, total_results[i]);
    }
    long union_endtime = Util::get_cur_time();
    for (std::map<std::string, std::vector<std::string> *>::iterator it = query_to_res.begin(); it != query_to_res.end(); it++) // 要改 确实要改 用都用不了
        delete it->second;
    std::string final_result;
    for (int i = 0; i < union_res.size(); i++)
    {
        final_result += (union_res.at(i) + "\n");
    }
    data["结果"] = final_result;
    return data;
};

/*****************************************************************
 * 函数名称： int database::Database::DbBackUp(std::vector<GstoreConnector *> &servers, const std::string &path,  
 *                                            const std::string version)
 * 功能描述： 备份数据库
 * 参数说明： 节点，字符串为数据库名称和备份路径
 * 返回值：   int值
 ******************************************************************/
string database::Database::DbBackUp(std::vector<GstoreConnector *> &servers, const std::string &path, const std::string version)
{

    int part = servers.size();
    BackRestoreThreadArgs build_threads_args[part];
    pthread_t backup_pthrds[part];
    for (int i = 0; i < part; i++)
    {
        build_threads_args[i].server_ = servers[i];
        build_threads_args[i].db_name_ = this->get_database_id_();
        build_threads_args[i].path_ = path;
        build_threads_args[i].version_ = version;
        if (pthread_create(&backup_pthrds[i], NULL, BackupThread, &build_threads_args[i]) != 0)
            throw runtime_error("creates backup thread error!");
    }

    for (int i = 0; i < part; i++)
        pthread_join(backup_pthrds[i], NULL);

    for (int i = 0; i < part; i++)
    {

        if (build_threads_args[i].res_.find("successfully") != std::string::npos)
        {
            return build_threads_args[i].res_;
        }
    }

    return "fail";
};

/*****************************************************************
 * 函数名称： int database::Database::DbRestore(std::vector<GstoreConnector *> &servers, const std::string &path)
 * 功能描述： 还原数据库
 * 参数说明： 节点，字符串为数据库名称和还原后保存路径
 * 返回值：   int值
 ******************************************************************/
std::string database::Database::DbRestore(std::vector<GstoreConnector *> &servers, const std::string &path)
{
    int part = servers.size();
    BackRestoreThreadArgs build_threads_args[part];
    pthread_t restore_pthrds[part];
    for (int i = 0; i < part; i++)
    {
        build_threads_args[i].server_ = servers[i];
        build_threads_args[i].db_name_ = this->get_database_id_();
        build_threads_args[i].path_ = path;
        if (pthread_create(&restore_pthrds[i], NULL, RestoreThread, &build_threads_args[i]) != 0)
            throw runtime_error("creates restore thread error!");
    }
    for (int i = 0; i < part; i++)
        pthread_join(restore_pthrds[i], NULL);
    for (int i = 0; i < part; i++)
    {

        if (build_threads_args[i].res_.find("successfully") != std::string::npos)
        {
            return build_threads_args[i].res_;
        }
    }

    return "fail";
};

/*****************************************************************
 * 函数名称： nlohmann::json database::Database::DbMonitor(std::vector<GstoreConnector *> &servers)
 * 功能描述： 监控数据库,查询相关数据
 * 参数说明： 节点，字符串为数据库名称
 * 返回值：   返回相关信息
 ******************************************************************/
nlohmann::json database::Database::DbMonitor(std::vector<GstoreConnector *> &servers)
{
    nlohmann::json monitor_data;
    int part = servers.size();
    MNV mnv[part];
    pthread_t monitor_pthrds[part];
    for (int i = 0; i < part; i++)
    {
        mnv[i].db_name_ = this->get_database_id_();
        mnv[i].server_ = servers[i];
        if (pthread_create(&monitor_pthrds[i], NULL, MonitorThread, &mnv[i]) != 0)
            throw runtime_error("creates monitor thread error!");
    }
    for (int i = 0; i < part; i++)
        pthread_join(monitor_pthrds[i], NULL);

    for (int i = 0; i < part; i++)
    {
        monitor_data[i]["节点ip"] = servers[i]->serverIP;
        monitor_data[i]["节点port"] = servers[i]->serverPort;
        monitor_data[i]["信息"] = mnv[i].res_;
    }

    return monitor_data;
};

/*****************************************************************
 * 函数名称： int database::Database::DeleteDb(std::vector<GstoreConnector *> &servers, const std::string &db_name)
 * 功能描述： 删除数据库
 * 参数说明： 节点，字符串为数据库名称，db类
 * 返回值：   int值
 ******************************************************************/
int database::Database::DeleteDb(std::vector<GstoreConnector *> &servers, const std::string &db_name)
{
    int part = servers.size();
    BuildThreadArgs build_threads_args[part];
    pthread_t delete_pthrds[part];
    for (int i = 0; i < part; i++)
    {

        build_threads_args[i].server_ = servers[i];
        build_threads_args[i].db_name_ = this->get_database_id_();
        if (pthread_create(&delete_pthrds[i], NULL, DeleteThread, &build_threads_args[i]) != 0)
            throw runtime_error("creates delete thread error!");
    }
    for (int i = 0; i < part; i++)
        pthread_join(delete_pthrds[i], NULL);

    return 0;
};