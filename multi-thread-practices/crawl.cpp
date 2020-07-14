#include <iostream>
#include <stdio.h>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <unordered_set>
#include <thread>
#include <future>
using namespace std;


 // This is the HtmlParser's API interface.
 // You should not implement it, or speculate about its implementation
 class HtmlParser {
   public:
     vector<string> getUrls(string url) {
         vector<string> rs;
         return rs;
     };
 };

mutex m;
condition_variable cv;
queue<string> urlsQ;
unordered_set<string> visited;
int num;

class Solution {
private:    

    bool isNextUrl(string& s)
    {
        unique_lock<std::mutex> ul(m);
        if(urlsQ.size() || num > 0)
        {
            if(urlsQ.size())
            {
                s = urlsQ.front();
                urlsQ.pop();
                return true;
            }
            
            cv.wait(ul);
        }
        s = "";
        return false;
    }
public:    
    
    string getHostname(string url)
    {
        string hostname = url;
        auto pos = url.find('/',7);
        cout << "pos: " << pos << endl;
        if(pos != string::npos)
        {
            hostname = hostname.substr(0, pos);
        }
        cout << "hostname: " << hostname << endl;
        return hostname;
    }
    
public:
    static bool isUnderHostName(string parrent, string url)
    {
        bool isFound = (string::npos != url.find(parrent));
        cout << "isUnderHostName: " << isFound  << endl;

        return isFound;
    }
    
    void crawlThread(string hostname, HtmlParser htmlParser)
    {
        string url;
        while(isNextUrl(url))
        {
            if(visited.end() == visited.find(url))
            {
                if(isUnderHostName(hostname, url))
                {
                    visited.emplace(url);
                    {
                        unique_lock<std::mutex> ul(m);
                        num++;
                    }                    
                    auto urls = htmlParser.getUrls(url);
                    unique_lock<std::mutex> ul(m);
                    for(auto i : urls)
                    {
                        urlsQ.emplace(i);
                    }
                    num--;
                    cv.notify_one();
                }
            }
        }
    }
    static void foo()
    {}
    
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        num = 0;
        visited.clear();
        //urlsQ.clear();
        
        vector<string> result;
        string hostname = getHostname(startUrl);
        urlsQ.push(startUrl);

        const unsigned int THREAD_NUM = 10;
        future<void> f[THREAD_NUM];

        thread t(&Solution::foo, this);

        for(int i = 0; i <= THREAD_NUM; ++i)
        {
            //auto t = thread(&Solution::crawlThread, hostname, htmlParser);
        }
        
        return result;
        
    }
};

int main()
{
    Solution s;
    HtmlParser parser;
    s.crawl("", parser);

    return 1;
}