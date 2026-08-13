#include <stdbool.h>
#include <stdio.h>

int page_in_frame(int frames[], int size, int page);
int get_lru_frame_index(int last_used[], int size);
void print_status(int frames[], int size, bool hit, int request);

void simulate_lru(int page_requests[], int num_requests, int num_frames) {
    int frames[num_frames];
    int last_used[num_frames];
    int page_faults = 0;

    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    for (int time = 0; time < num_requests; time++) {
        int page = page_requests[time];
        bool hit = false;

        int frame_index;
        if ((frame_index = page_in_frame(frames, num_frames, page)) != -1) {
            hit = true;
            last_used[frame_index] = time;
        }

        if (!hit) {
            page_faults++;
            frame_index = get_lru_frame_index(last_used, num_frames);
            frames[frame_index] = page;
            last_used[frame_index] = time;
        }

        print_status(frames, num_frames, hit, page);
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int page_in_frame(int frames[], int size, int page) {
    for (int i = 0; i < size; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

int get_lru_frame_index(int last_used[], int size) {
    int result = 0;
    int min_time = last_used[0];
    for (int i = 1; i < size; i++) {
        if (last_used[i] < min_time) {
            min_time = last_used[i];
            result = i;
        }
    }
    return result;
}

void print_status(int frames[], int size, bool hit, int request) {
    printf("Request: %d\tStatus: %s\tRam State: [", request,
           hit ? "HIT" : "FAULT");
    for (int i = 0; i < size; i++) {
        printf("%d", frames[i]);
        if (i != size - 1)
            printf(", ");
    }
    printf("]\n");
}

int main() {
    int requests[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int num_requests = sizeof(requests) / sizeof(requests[0]);

    simulate_lru(requests, num_requests, 3);
    return 0;
}
