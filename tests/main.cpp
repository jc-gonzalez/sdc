#include <iostream>
#include <sstream>
using namespace std;

#include "msgtypes.h"

#include "sdc.h"
using namespace SDC;

#define V(a) #a ": " << a

void test_ProductMetadata();

int main(int argc, char * argv[])
{
    stringstream ss;
    int k = 0;

    Value::setDefaultType(Value::DICT);

    Value d;

    for(unsigned int i = 0; i < 10; ++i) {
        ss.str("");
        ss << "key_" << i;
        string k = ss.str();

        ss.str("");
        ss << "The value no." << i;
        string v = ss.str();

        d[k] = v;
    }
    cout << k++ << ":: " << d << endl;

    Value a(Value::ARRAY);

    for(unsigned int i = 0; i < 5; ++i) {
        ss.str("");
        ss << "The element no." << i;
        string s = ss.str();
        a[i] = s;

        Value & v = a[i];
        v = 4;
    }

    cout << k++ << ":: " << a << endl;

    Value c;
    c["d"] = d;
    c["a"] = a;

    cout << k++ << ":: " << c << endl;

    string s1 = c["d"]["key_2"].asStr();
    int    i1 = c["a"][2].asInt();

    cout << k++ << ":: " << V(s1) << ", " << V(i1) << endl;

    string ser;
    c.serialize(ser);

    Value cc;
    cc.deserialize(ser);

    string s2 = c["d"]["key_2"].asStr();
    int    i2 = c["a"][2].asInt();

    cout << k++ << ":: " << V(s2) << ", " << V(i2) << endl;

    /* ************************************************** */
    test_ProductMetadata();

    return 0;
}

void test_ProductMetadata()
{
    QPF::ProductMetadata z1, z2, z3;

    z1.startTime = "the startTime";
    z1.endTime = "the endTime";
    z1.regTime = "the regTime";
    z1.instrument = "the instrument";
    z1.obsMode = "the obsMode";
    z1.creator = "the creator";
    z1.productId = "the productId";
    z1.productType = "the productType";
    z1.productVersion = "the productVersion";
    z1.productStatus = "the productStatus";
    z1.productSize = 42;
    z1.url = "the url";

    z2 = z1;

    cerr << V(z1.getData()) << endl;
    cerr << V(z2.getData()) << endl;
}

/*
void test_ProductCollection()
{
    ProductCollection z1, z2, z3;

    std::map<ProductType, ProductMetadata> productList;

    virtual void toFields() {
        productList.clear();
        for (unsigned int i = 0; i < data.size(); ++i) {
            SDC::Value & v = data[i];
            ProductType t = v["productType"].asStr();
            ProductMetadata m;
            m.setData(v);
            productList[t] = m;
        }
    }

    virtual void toData() {
        data.clear();
        data.setType(SDC::Value::DICT);
        std::map<ProductType,
                ProductMetadata>::iterator it = productList.begin();
        while (it != productList.end()) {
            ProductMetadata & m = it->second;
            data.asDict()[m.productType] = m.getData();
//            data << m.getData();
            ++it;
        }
    }
}

void test_ProductList()
{
    ProductList z1, z2, z3;

    std::vector<ProductMetadata> productList;

    virtual void toFields() {
        productList.clear();
        for (unsigned int i = 0; i < data.size(); ++i) {
            SDC::Value & v = data[i];
            ProductMetadata m;
            m.setData(v);
            productList.push_back(m);
        }
    }

    virtual void toData() {
        data.clear();
        data.setType(SDC::Value::ARRAY);
        for (unsigned int i = 0; i < productList.size(); ++i) {
            data << productList.at(i).getData();
        }
    }
}

void test_StringList()
{
    StringList z1, z2, z3;

    std::vector<std::string> items;

    virtual void toFields() {
        items.clear();
        for (unsigned int i = 0; i < data.size(); ++i) {
            items.push_back(data[i].asStr());
        }
    }

    virtual void toData() {
        data.clear();
        data.setType(SDC::
Value::ARRAY);
        for (unsigned int i = 0; i < items.size(); ++i) {
            data << items.at(i);
        }
    }
}

void test_ParameterList()
{
    ParameterList z1, z2, z3;

    std::map<std::string, std::string> paramList;

    virtual void toFields() {
        paramList.clear();
        for (std::pair<std::string, SDC::Value> const & kv : data.asDict()) {
            paramList[kv.first] = kv.second.asStr();
        }
    }

    virtual void toData() {
        data.clear();
        data.setType(SDC::Value::DICT);
        for (std::pair<std::string, std::string> const & kv : paramList) {
            std::string & key = const_cast<std::string&>(kv.first);
            data[key] = SDC::Value(kv.second.c_str());
        }
    }
}

void test_TaskInfo()
{
    TaskInfo z1, z2, z3;

    TaskInfo() {}
    z1.taskName = "the taskName";
    z1.taskPath = "the taskPath";
    z1.taskStart = "the taskStart";
    z1.taskEnd = "the taskEnd";
    z1.taskExitCode = "the taskExitCode";
    z1.taskStatus = "the taskStatus";
    z1.inputs = "the inputs";
    z1.outputs = "the outputs";
    z1.params = "the params";
    z1.taskData = "the taskData";

    virtual void toFields() {
        taskName     = data["taskName"    ].asStr();
        taskPath     = data["taskPath"    ].asStr();
        taskStart    = data["taskStart"   ].asStr();
        taskEnd      = data["taskEnd"     ].asStr();
        taskExitCode = data["taskExitCode"].asInt();
        taskStatus   = static_cast<TaskStatus>(data["taskStatus"  ].asInt());
        inputs .setData(data["inputs" ]);
        outputs.setData(data["outputs"]);
        params .setData(data["params" ]);
        taskData      = data["taskData"];
    }

    virtual void toData() {
        data["taskName"     ] = taskName;
        data["taskPath"     ] = taskPath;
        data["taskStart"    ] = taskStart;
        data["taskEnd"      ] = taskEnd;
        data["taskExitCode" ] = taskExitCode;
        data["taskStatus"   ] = static_cast<int>(taskStatus);
        data["inputs" ]  = inputs .getData();
        data["outputs"]  = outputs.getData();
        data["params" ]  = params .getData();
        data["taskData"] = taskData;
    }
}

void test_TaskAgentInfo()
{
    TaskAgentInfo z1, z2, z3;

    int         total;
    int         maxnum;
    int         running;
    int         waiting;
    int         paused;
    int         stopped;
    int         failed;
    int         finished;
    int         load1min;
    int         load5min;
    int         load15min;
    int         uptimesecs;
    std::string name;
    std::string client;
    std::string server;

    TaskAgentInfo() :
        total(0),
        maxnum(0),
        running(0),
        waiting(0),
        paused(0),
        stopped(0),
        failed(0),
        finished(0),
        load1min(0),
        load5min(0),
        load15min(0),
        uptimesecs(0) {}


    virtual void toFields() {
        total      = data["total"].asInt();
        maxnum     = data["maxnum"].asInt();
        running    = data["running"].asInt();
        waiting    = data["waiting"].asInt();
        failed     = data["failed"].asInt();
        finished   = data["finished"].asInt();
        load1min   = data["load1min"].asInt();
        load5min   = data["load5min"].asInt();
        load15min  = data["load15min"].asInt();
        uptimesecs = data["uptimesecs"].asInt();
        name       = data["name"].asStr();
        client     = data["client"].asStr();
        server     = data["server"].asStr();
    }

    virtual void toData() {
        data["total"]      = total;
        data["maxnum"]     = maxnum;
        data["running"]    = running;
        data["waiting"]    = waiting;
        data["failed"]     = failed;
        data["finished"]   = finished;
        data["load1min"]   = load1min;
        data["load5min"]   = load5min;
        data["load15min"]  = load15min;
        data["uptimesecs"] = uptimesecs;
        data["name"]       = name;
        data["client"]     = client;
        data["server"]     = server;
    }
}

void test_MessageHeader()
{
    MessageHeader z1, z2, z3;

    z1.msgId = "the msgId";
    z1.msgVersion = "the msgVersion";
    z1.source = "the source";
    z1.destination = "the destination";
    z1.path = "the path";
    z1.dateCreation = "the dateCreation";
    z1.dateTransmission = "the dateTransmission";
    z1.dateReception = "the dateReception";
    z1.crc = "the crc";

    virtual void toFields() {
        msgId            = data["msgId"           ].asInt();
        msgVersion       = data["msgVersion"      ].asInt();
        source           = data["source"          ].asStr();
        destination      = data["destination"     ].asStr();
        dateCreation     = data["dateCreation"    ].asStr();
        dateTransmission = data["dateTransmission"].asStr();
        dateReception    = data["dateReception"   ].asStr();
        crc              = data["crc"             ].asInt();
        path.setData(data["path"]);
    }

    virtual void toData() {
        data["msgId"           ] = msgId;
        data["msgVersion"      ] = msgVersion;
        data["source"          ] = source;
        data["destination"     ] = destination;
        data["dateCreation"    ] = dateCreation;
        data["dateTransmission"] = dateTransmission;
        data["dateReception"   ] = dateReception;
        data["crc"             ] = crc;
        data["path"] = path.getData();
    }
}

void test_Message()
{
    Message z1, z2, z3;

    z1.header = "the header";
    virtual void toFields() {}
    virtual void toData() {}
}

void test_Message_INDATA()
{
    Message_INDATA z1, z2, z3;

    z1.productsMetadata = "the productsMetadata";

    virtual void toFields() {
        header          .setData(data["header"]);
        productsMetadata.setData(data["productcsMetadata"]);
    }
    virtual void toData() {
        data["header"]            = header          .getData();
        data["productcsMetadata"] = productsMetadata.getData();
    }
}

void test_Message_DATA_Exchange()
{
    Message_DATA_Exchange z1, z2, z3;

    z1.variables = "the variables";

    virtual void toFields() {
        header   .setData(data["header"]);
        variables.setData(data["variables"]);
    }
    virtual void toData() {
        data["header"]    = header   .getData();
        data["variables"] = variables.getData();
    }
}

void test_Message_TASK_Processing()
{
    Message_TASK_Processing z1, z2, z3;

    z1.task = "the task";
    std::string rule;

    virtual void toFields() {
        header.setData(data["header"]);
        task  .setData(data["task"]);
        rule = data["rule"].asStr();
    }
    virtual void toData() {
        data["header"] = header.getData();
        data["task"]   = task  .getData();
        data["rule"]   = rule;
    }
}
*/
