/* ---  伪代码  --- */

#define buffer_size 10
typedef int Item;
Item buffer[buffer_size];
int in = 0;
int out = 0;
Item nextConsumed;
Item nextProduct = 1;

int main(int argc, char const *argv[])
{
    // 生产者
    while (true){
        while((in+1)%buffer_size == out)  // 终止
        ;
        buffer[in] = nextProduct;
        in = (in+1)%buffer_size;
    }
    
    // 消费者
    while (true){
        while (in == out)  // 终止
            ;
        nextConsumed = buffer[out];
        out = (out+1)%buffer_size;
    }
    return 0;
}


