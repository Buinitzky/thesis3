#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <string.h>
#include <linux/sockios.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

/****************MODIFICADO****************/
/*	struct for ethtool driver	*/
struct ethtool_cmd {
unsigned int cmd;
unsigned int	supported;	/* Features this interface supports */
unsigned int	advertising;	/* Features this interface advertises */
unsigned short	speed;	 /* The forced speed, 10Mb, 100Mb, gigabit */
unsigned char	duplex;	 /* Duplex, half or full */
unsigned char	port;	 /* Which connector port */
unsigned char	phy_address;
unsigned char	transceiver;	/* Which tranceiver to use */
unsigned char	autoneg;	/* Enable or disable autonegotiation */
unsigned int	maxtxpkt;	/* Tx pkts before generating tx int */
unsigned int	maxrxpkt;	/* Rx pkts before generating rx int */
unsigned int	reserved[4];
};

#define SPEED_10	 10
#define SPEED_100	 100
#define SPEED_1000	 1000
#define SPEED_10000	 10000

/* Duplex, half or full. */
#define DUPLEX_HALF	 0x00
#define DUPLEX_FULL	 0x01

#define ETHTOOL_GSET	 0x00000001 /* Get settings command for ethtool */



char* obtenerIp() {
    int iSocket = -1;
    struct if_nameindex* pIndex = 0;
    struct if_nameindex* pIndex2 = 0;
    char ip [15];
    if ((iSocket = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return NULL;
    }
    pIndex = pIndex2 = if_nameindex();
    pIndex++;
    if ((pIndex != NULL) && (pIndex->if_name != NULL)) {
        struct ifreq req;
        strncpy(req.ifr_name, pIndex->if_name, IFNAMSIZ);
        if (ioctl(iSocket, SIOCGIFADDR, &req) < 0) {
            perror("ioctl");
            close(iSocket);
            return NULL;
        }
        strcpy(ip, inet_ntoa(((struct sockaddr_in*) &req.ifr_addr)->sin_addr));
        if_freenameindex(pIndex2);
        close(iSocket);
        return ip;
    }
}

char **split ( char *string, const char sep) {

    char **lista;
    char *p = string;
    int i = 0;

    int pos;
    const int len = strlen (string);

    lista = (char **) malloc (sizeof (char *));
    if (lista == NULL) { /* Cannot allocate memory */
    return NULL;
    }

    lista[pos=0] = NULL;

    while (i < len) {

    while ((p[i] == sep) && (i < len))
    i++;

    if (i < len) {

    char **tmp = (char **) realloc (lista , (pos + 2) * sizeof (char *));
    if (tmp == NULL) { /* Cannot allocate memory */
    free (lista);
    return NULL;
    }
    lista = tmp;
    tmp = NULL;

    lista[pos + 1] = NULL;
    lista[pos] = (char *) malloc (sizeof (char));
    if (lista[pos] == NULL) { /* Cannot allocate memory */
    for (i = 0; i < pos; i++)
    free (lista[i]);
    free (lista);
    return NULL;
    }

    int j = 0;
    for (i; ((p[i] != sep) && (i < len)); i++) {
    lista[pos][j] = p[i];
    j++;

    char *tmp2 = (char *) realloc (lista[pos],(j + 1) * sizeof (char));
    if (lista[pos] == NULL) { /* Cannot allocate memory */
    for (i = 0; i < pos; i++)
    free (lista[i]);
    free (lista);
    return NULL;
    }
    lista[pos] = tmp2;
    tmp2 = NULL;
    }
    lista[pos][j] = '\0';
    pos++;
    }
    }

    return lista;
}
/****************MODIFICADO****************/
char* getName(){
 int iSocket = -1;
    struct if_nameindex* pIndex = 0;
    struct if_nameindex* pIndex2 = 0;
    struct ifreq req;
    char ip [10];
  
    if ((iSocket = socket(PF_INET ,SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return NULL;
    }
    pIndex = pIndex2 = if_nameindex();
    while ((pIndex != NULL) && (pIndex->if_name != NULL)) {
        if(pIndex->if_name[0]!='l'){
            strncpy(req.ifr_name, pIndex->if_name, IFNAMSIZ);
            if (ioctl(iSocket, SIOCGIFADDR, &req) >= 0) {
                strcpy(ip, pIndex->if_name);
                if_freenameindex(pIndex2);
                close(iSocket);
                return ip;
                
            }
        }
        pIndex++;
    }

    printf("\nNo se detecto ninguna interfaz de red activa\n");
    exit(-1);
}
/****************MODIFICADO****************/
float getVmCable(char* ethname){
    int returnValue;
    int fd;
    struct ifreq ifr;
    struct ethtool_cmd ecmd;

    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, ethname);	//eth0

    
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) 
    {
    fprintf(stdout,"Cannot get control socket");
    return -1;
    }
    ecmd.cmd = ETHTOOL_GSET;
    ifr.ifr_data = (caddr_t)&ecmd;
    returnValue = ioctl(fd, SIOCETHTOOL, &ifr);


    if (returnValue != 0)
    {
        fprintf(stdout,"Cannot get device settings");
        exit(-1);
    }

    switch (ecmd.speed)
    {
        case SPEED_10:
        {
            return SPEED_10;
        }
        case SPEED_100:
        {
            return SPEED_100;
        }
        case SPEED_1000:
        {
            return SPEED_1000;
        }
        case SPEED_10000:
        {
            return SPEED_10000;
        }
        default:
        {
            fprintf(stdout,"Speed reading faulty %d  ", ecmd.speed);
            break;
        }
    }
    return 0;
}