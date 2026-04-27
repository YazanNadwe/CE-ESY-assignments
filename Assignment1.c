#include <stdio.h>
#include <string.h>

// تعريف حجم المخزن
#define SIZE 10

// تعريف هيكل المخزن الدائري كما ورد في التوصيف
struct CircularBuffer {
    char buffer[SIZE];
    int head;   // مؤشر الكتابة
    int tail;   // مؤشر القراءة
    int count;  // عداد العناصر
};

// دالة التهيئة
void init(struct CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// دالة التحقق من الامتلاء
int isFull(struct CircularBuffer *cb) {
    if (cb->count == SIZE) {
        return 1; // ممتلئ
    }
    return 0; // غير ممتلئ
}

// دالة التحقق من الفراغ
int isEmpty(struct CircularBuffer *cb) {
    if (cb->count == 0) {
        return 1; // فارغ
    }
    return 0; // غير فارغ
}

// دالة الكتابة (إضافة محرف)
void write(struct CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("Buffer Overflow\n");
    } else {
        cb->buffer[cb->head] = data;
        cb->head = (cb->head + 1) % SIZE; // التحريك بشكل دائري
        cb->count = cb->count + 1;
    }
}

// دالة القراءة (إزالة محرف)
char read(struct CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("Buffer Underflow\n");
        return '\0';
    } else {
        char data = cb->buffer[cb->tail];
        cb->tail = (cb->tail + 1) % SIZE; // التحريك بشكل دائري
        cb->count = cb->count - 1;
        return data;
    }
}

// الدالة الرئيسية
int main() {
    struct CircularBuffer cb;
    init(&cb); // تهيئة

    char name[50];
    char suffix[] = "CE-ESY";

    // طلب الاسم من المستخدم 
    printf("Enter your name: ");
    scanf("%s", name);

    // دمج اللاحقة مع الاسم 
    strcat(name, suffix);
    printf("Result string: %s\n", name);

    // تخزين المحارف في المخزن الدائري 
    for (int i = 0; i < strlen(name); i++) {
        write(&cb, name[i]);
    }

    // القراءة من المخزن وعرض النتيجة 
    printf("Reading from Buffer: ");
    while (isEmpty(&cb) == 0) {
        char c = read(&cb);
        printf("%c", c);
    }

    printf("\nDone.\n");
    return 0;
}
