#include "../includes/ft_malcolm.h"

typedef struct {
    char *name;
    char **args;
} test_case_t;

int run_test(const test_case_t test) {
    pid_t pid;
    int status;

    printf("\nRunning test: %s\n", test.name);
    printf("Command:");
    for (int i = 0; test.args[i] != NULL; i++) {
        printf(" %s", test.args[i]);
    }
    printf("\n");

    pid = fork();
    if (pid == -1) {
        perror("Fork error");
        return -1;
    }

    if (pid == 0) {
        execve(PROGRAM_NAME, test.args, NULL);
        perror("Execve error");
        exit(1);
    }

    waitpid(pid, &status, 0);

    return 0;
}

void run_all_tests(test_case_t tests[], const int num_tests) {
    for (int i = 0; i < num_tests; i++) {
       run_test(tests[i]);
    }
}

int main() {
    char *args1[] = {PROGRAM_NAME, NULL};
    char *args2[] = {PROGRAM_NAME, "arg1", "arg2", "arg3", "arg4", NULL};
    char *args3[] = {PROGRAM_NAME, "192.168.1.1111111", "ff:bb:ff:ff:ee:ff", "10.12.10.22", "ff:bb:ff:ff:ee:ff", NULL};
    char *args4[] = {PROGRAM_NAME, "10.12.10.22", "aaa:bb:cc:dd:ee:fff", "10.12.10.22", "ff:bb:ff:ff:ee:ff", NULL};
    char *args5[] = {PROGRAM_NAME, "abcde", "aaa:bb:cc:dd:ee:fff", "10.12.10.22", "ff:bb:ff:ff:ee:ff", NULL};
    char *args6[] = {PROGRAM_NAME, "192.168.1.1", "ff:bb:ff:ff:ee:ff", "192.168.1.1", "ff:bb:ff:ff:ee:ff", NULL};

    test_case_t tests[] = {
        {
            .name = "Basic test without arguments",
            .args = args1,
        },
        {
            .name = "Basic test with four arguments",
            .args = args2,
        },
        {
            .name = RED "Invalid IP Address" RESET,
            .args = args3,
        },
        {
            .name = RED "Invalid MAC Address" RESET,
            .args = args4,
        },
        {
            .name = RED "Invalid character in IP Address" RESET,
            .args = args5,
        },
        {
            .name = GREEN "Valid arguments" RESET,
            .args = args6,
        },
    };

    run_all_tests(tests, sizeof(tests) / sizeof(tests[0]));

    return 0;
}