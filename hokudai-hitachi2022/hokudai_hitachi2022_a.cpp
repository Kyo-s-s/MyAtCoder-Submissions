#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define all(x) (x).begin(),(x).end()
const int INF = 1 << 28;


//Assign one job to each worker and execute the job

struct IOServer {
    vector<int> selected_jobs;
    int T_max;
    int V, E;
    vector<vector<pair<int,int>>> edge;
    vector<vector<int>> dist;
    int N_worker, N_job;
    
    class Worker {
        public:
            int N_type, L, pos, pos2, dist;
            set<int> type;
    };

    vector<Worker> worker;

    class Job {
        public:
            int id, type, N, v;
            vector<pair<int, ll>> reward; 
            vector<ll> score;
            vector<int> depend;
    };

    vector<Job> job;


    //caliculate distance
    void dij() {
        dist.resize(V);
        for (int i = 0; i < V; i++){
            dist[i].resize(V);
            for (int j = 0; j < V; j++) dist[i][j] = 1e9;
            dist[i][i] = 0;
            priority_queue<pair<int, int>, std::vector<pair<int, int>>, std::greater<pair<int, int>>> q;
            q.push({0, i});
            while (!q.empty()) {
                pair<int, int> t = q.top();
                q.pop();
                if (dist[i][t.second] != t.first) continue;
                for (auto e : edge[t.second]) {
                    if (dist[i][e.first] > dist[i][t.second] + e.second){
                        dist[i][e.first] = dist[i][t.second] + e.second;
                        q.push({dist[i][e.first], e.first});
                    }
                }
            }
        }
    }

	void input(){
        cin >> T_max;
        cin >> V >> E;
        edge.resize(V);
        for (int i = 0; i < E; i++){
            int f, g, h;
            cin >> f >> g >> h;
            f--; g--;
            edge[f].push_back({g, h});
            edge[g].push_back({f, h});
        }
        dij();
        cin >> N_worker;
        worker.resize(N_worker);
        for (int i = 0; i < N_worker; i++){
            cin >> worker[i].pos >> worker[i].L >> worker[i].N_type;
            for (int j = 0; j < worker[i].N_type; j++){
                int f;
                cin >> f;
                f--;
                worker[i].type.insert(f);
            }
            worker[i].pos--;
            worker[i].pos2 = worker[i].pos;
            worker[i].dist = 0;
        }
        cin >> N_job;
        job.resize(N_job);
        for (int i = 0; i < N_job; i++){
            cin >> job[i].id >> job[i].type >> job[i].N >> job[i].v;
            job[i].id--;
            job[i].type--;
            job[i].v--;
            int N_reward;
            cin >> N_reward;
            for (int j = 0; j < N_reward; j++){
                int f, g;
                cin >> f >> g;
                f--;
                job[i].reward.push_back({f, g});
            }
            job[i].reward.push_back({(int)T_max + 2, job[i].reward[N_reward-1].second});
            job[i].score.resize(T_max + 2,0);
            job[i].score[0] = 0;
            int it = 0;
            for (int j = 0; j < T_max+1; j++){
                if (it == 0) {
                    job[i].score[j+1] = 0;
                    if (j >= job[i].reward[it].first){
                        it++;
                    }
                    continue;
                }
                ll now_score = job[i].reward[it-1].second + (j - job[i].reward[it-1].first) * 
                    (job[i].reward[it].second - job[i].reward[it-1].second) / (job[i].reward[it].first-job[i].reward[it-1].first);
                job[i].score[j+1] = job[i].score[j] + now_score;
                if (j >= job[i].reward[it].first){
                    it++;
                }
            }
            int N_depend;
            cin >> N_depend;
            for (int j = 0; j < N_depend; j++){
                int f;
                cin >> f;
                f--;
                job[i].depend.push_back(f);
            }
        }
    }
} IOServer;


struct solver {
    //determine worker's job
    vector<map<int, pair<int, int>>> worker_jobs; // finish, {job_id, pos}

    struct Job {
        int id, type, N, v;
        ll score;
        int start_time, finish_time;
        vector<int> depend;
    };

    enum class Action {
        MOVE,
        EXECUTE,
        STAY,
    };

    void init() {
        worker_jobs.resize(IOServer.N_worker);
        worker_jobs.resize(IOServer.N_worker);
        for (int i = 0; i < IOServer.N_worker; i++) {
            worker_jobs[i][0] = {-1, IOServer.worker[i].pos};
        }
        map<int, int> selected_jobs; // {id, finish_time}
        vector<vector<Action>> schejule(IOServer.N_worker, vector<Action>(IOServer.T_max, Action::STAY));

        for (int loop = 0; loop < 10; loop++) {

        for (int w = 0; w < IOServer.N_worker; w++) {
            priority_queue<Job, vector<Job>, function<bool(Job, Job)>> queue([](Job a, Job b) {
                return a.score < b.score;
            });
            for (int j = 0; j < IOServer.N_job; j++) {
                if (selected_jobs.count(j)) continue;
                if (IOServer.worker[w].type.count(IOServer.job[j].type) == 0) continue;
                if (!all_of(all(IOServer.job[j].depend), [&](int d) { return selected_jobs.count(d); })) continue;
                int job_day = (IOServer.job[j].N + IOServer.worker[w].L - 1) / IOServer.worker[w].L;
                for (int start = IOServer.job[j].reward[0].first + 1; start + job_day < IOServer.job[j].reward[IOServer.job[j].reward.size() - 2].first; start += IOServer.T_max / 30) {
                    ll score = 0, job_N = IOServer.job[j].N;
                    for (int t = start; t <= start + job_day; t++) {
                        score += IOServer.job[j].score[t] * min(job_N, (ll)IOServer.worker[w].L);
                        job_N -= min(job_N, (ll)IOServer.worker[w].L);
                    }
                    queue.push({j, IOServer.job[j].type, IOServer.job[j].N, IOServer.job[j].v, score, start, start + job_day, IOServer.job[j].depend});
                }
            }

            while (!queue.empty()) {
                Job job = queue.top(); queue.pop();
                if (selected_jobs.count(job.id)) continue;

                int start = job.start_time, finish = job.finish_time;
                if (!all_of(all(job.depend), [&](int d) { return selected_jobs.count(d) && selected_jobs[d] < start; })) continue;
                int prev_pos = IOServer.worker[w].pos;
                for (auto [fin, id_pos] : worker_jobs[w]) {
                    if (fin < start) {
                        prev_pos = id_pos.second;
                    } else {
                        break;
                    }
                }
                int move_day = IOServer.dist[prev_pos][IOServer.job[job.id].v];
                if (loop < 5 && move_day > (loop + 1) * 5) continue;
                if (start - move_day < 0) continue;
                bool ok = true;
                for (int t = start - move_day; t <= finish; t++) {
                    if (schejule[w][t] != Action::STAY) {
                        ok = false;
                        break;
                    }
                }
                if (!ok) continue;
                for (int i = start - move_day; i < start; i++) {
                    schejule[w][i] = Action::MOVE;
                }
                for (int i = start; i <= finish; i++) {
                    schejule[w][i] = Action::EXECUTE;
                }
                worker_jobs[w][finish] = {job.id, IOServer.job[job.id].v};
                selected_jobs[job.id] = finish;
            }
        }

        }
    }

    void solve() {
        vector<int> worker_job(IOServer.N_worker, -1);
        set<int> finished_jobs;

        auto next_job = [&](int w, int t) -> int {
            for (auto [fin, id_pos] : worker_jobs[w]) {
                if (finished_jobs.count(id_pos.first)) continue;
                if (t < fin) {
                    return id_pos.first;
                }
            }
            return -1;
        };

        for (int w = 0; w < IOServer.N_worker; w++) {
            worker_job[w] = next_job(w, 0);
        }

        for (int t = 0; t < IOServer.T_max; t++) {
            set<int> finished_jobs_nxt = finished_jobs;
            for (int w = 0; w < IOServer.N_worker; w++) {

                if (worker_job[w] == -1) {
                    cout << "stay" << endl;
                    continue;
                }

                if (IOServer.job[worker_job[w]].v == IOServer.worker[w].pos && IOServer.worker[w].dist == 0) {
                    if (IOServer.job[worker_job[w]].N > 0
                        && IOServer.job[worker_job[w]].reward[0].first < t
                        && t < IOServer.job[worker_job[w]].reward[IOServer.job[worker_job[w]].reward.size() - 2].first
                        && all_of(all(IOServer.job[worker_job[w]].depend), [&](int d) { return finished_jobs.count(d); })
                    ) {
                        cout << "execute " << worker_job[w] + 1 << " " << min(IOServer.job[worker_job[w]].N, (int)IOServer.worker[w].L) << endl;
                        IOServer.job[worker_job[w]].N -= min(IOServer.job[worker_job[w]].N, (int)IOServer.worker[w].L);
                        if (IOServer.job[worker_job[w]].N == 0) {
                            finished_jobs_nxt.insert(worker_job[w]);
                        }
                    } else {
                        cout << "stay" << endl;
                    }

                    worker_job[w] = next_job(w, t + 1);
                } else {
                    if (IOServer.worker[w].pos != IOServer.job[worker_job[w]].v) {
                        IOServer.worker[w].dist = IOServer.dist[IOServer.worker[w].pos][IOServer.job[worker_job[w]].v];
                        IOServer.worker[w].pos = IOServer.job[worker_job[w]].v;
                    }
                    cout << "move " << IOServer.job[worker_job[w]].v + 1 << endl;
                    IOServer.worker[w].dist--;
                }
            }
            finished_jobs = finished_jobs_nxt;
        }


        ll score; 
        cin >> score;
    }

} solver;

int main(int argc, char *argv[]) {
    IOServer.input();
    solver.init();
    solver.solve();
}