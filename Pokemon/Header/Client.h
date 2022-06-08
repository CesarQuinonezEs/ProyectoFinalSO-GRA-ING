class Client
{
private:
    /* data */
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *mensaje[100];
    char buffer[1024] = {0};
public:
    Client(/* args */);
    int clientRead();
    void clientSend(int Damage);
    ~Client();
};

Client::Client(/* args */)
{
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
       exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
}
int Client::clientRead(){ 
valread = read(sock, buffer, 1024);
int aux = atoi(buffer);
return aux;
}
void Client::clientSend(int Damage){
std::string tmp = std::to_string(Damage);
const char *aux = tmp.c_str();
send(sock , aux, strlen(aux), 0 );
}
Client::~Client()
{
}
