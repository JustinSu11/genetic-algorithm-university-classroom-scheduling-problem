#include "organizer.h"
#include <algorithm>
#include <cmath>
#include <unordered_map>

static const int    WH = 10000;
static const double WS = 1.0;

// ---------------------------------------------------------------------------
// computeH — hard penalty
//   = (# capacity violations) + (# room-conflict pairs)
//
// Room-conflict pair (i, j): same room AND share a day AND time slots overlap.
//   Same day  : (classes[i].days & classes[j].days) != 0
//   Overlap   : max(start_i, start_j) < min(end_i, end_j)
//               where end = start + length
//
// Strategy: bucket classes by their assigned room index, then check pairs
// only within each bucket.  This is far cheaper than an O(n^2) all-pairs
// scan because most rooms hold ~11 classes on average (2418 / 221).
// ---------------------------------------------------------------------------
int computeH(const std::vector<int>& phi,
             const std::vector<Class>& classes,
             const std::vector<Room>& rooms)
{
    int H = 0;
    int n = (int)classes.size();

    // --- Capacity violations ---
    for (int i = 0; i < n; i++) {
        if (classes[i].enrollment > rooms[phi[i]].capacity) {
            H++;
        }
    }

    // --- Room conflicts: bucket by room index ---
    // buckets[r] = list of class indices assigned to room r
    std::unordered_map<int, std::vector<int>> buckets;
    buckets.reserve(rooms.size());
    for (int i = 0; i < n; i++) {
        buckets[phi[i]].push_back(i);
    }

    for (auto& kv : buckets) {
        const std::vector<int>& bucket = kv.second;
        int k = (int)bucket.size();
        for (int a = 0; a < k; a++) {
            for (int b = a + 1; b < k; b++) {
                int ci = bucket[a];
                int cj = bucket[b];

                // 1. Share at least one day?
                if ((classes[ci].days & classes[cj].days) == 0) continue;

                // 2. Time slots overlap?
                int start_i = classes[ci].startSlot;
                int end_i   = start_i + classes[ci].length;
                int start_j = classes[cj].startSlot;
                int end_j   = start_j + classes[cj].length;

                if (std::max(start_i, start_j) < std::min(end_i, end_j)) {
                    H++;
                }
            }
        }
    }

    return H;
}

// ---------------------------------------------------------------------------
// computeS — soft penalty (student travel distance)
//
// For each of the 7 days:
//   1. Collect all classes that meet on that day.
//   2. Sort them by startSlot.
//   3. For each consecutive pair (a, b), add enrollment_a * dist(room_a, room_b).
//
// Bitmask encoding (from csvparser.cpp via stoul(..., 2)):
//   "1010100" = Mon/Wed/Fri.  Leftmost char = Monday = bit 6 (MSB of 7-bit value).
//   To test day d (0=Mon … 6=Sun): dayBit = 1u << (6 - d)
// ---------------------------------------------------------------------------
double computeS(const std::vector<int>& phi,
                const std::vector<Class>& classes,
                const std::vector<Room>& rooms)
{
    double S = 0.0;
    int n = (int)classes.size();

    for (int d = 0; d < 7; d++) {
        unsigned int dayBit = 1u << (6 - d); // Monday=bit6, …, Sunday=bit0

        // Collect class indices that meet on this day
        std::vector<int> dayClasses;
        for (int i = 0; i < n; i++) {
            if (classes[i].days & dayBit) {
                dayClasses.push_back(i);
            }
        }

        if (dayClasses.size() < 2) continue;

        // Sort by start slot
        std::sort(dayClasses.begin(), dayClasses.end(), [&](int a, int b) {
            return classes[a].startSlot < classes[b].startSlot;
        });

        // Sum enrollment * euclidean distance for each consecutive pair
        for (int k = 0; k + 1 < (int)dayClasses.size(); k++) {
            int ci = dayClasses[k];
            int cj = dayClasses[k + 1];
            int ri = phi[ci];
            int rj = phi[cj];

            double dx = rooms[ri].x - rooms[rj].x;
            double dy = rooms[ri].y - rooms[rj].y;
            double dist = std::sqrt(dx * dx + dy * dy);

            S += classes[ci].enrollment * dist;
        }
    }

    return S;
}

// ---------------------------------------------------------------------------
// computeFitness  f = 1 / (1 + wh*H + ws*S)
// ---------------------------------------------------------------------------
double computeFitness(ChromosomeStruct& cs,
                      const std::vector<Class>& classes,
                      const std::vector<Room>& rooms)
{
    int    H = computeH(cs.chromosome, classes, rooms);
    double S = computeS(cs.chromosome, classes, rooms);
    cs.H = H;
    cs.S = S;
    cs.fitness = 1.0 / (1.0 + WH * H + WS * S);
    return cs.fitness;
}
