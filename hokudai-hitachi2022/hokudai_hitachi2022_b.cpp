#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define all(obj) (obj).begin(), (obj).end()
//Assign one job to each worker and execute the job

struct IOServer {
    vector<int> selected_jobs;
    int T_max;
    int V, E;
    vector<vector<pair<int, int>>> edge;
    vector<vector<int>> dist;
    int N_worker, N_job;
    int T_weather, N_weather;
    vector<vector<ld>> weather_graph;
    vector<int> c_weather;
    ld P_m, R_m, alpha;
    vector<vector<ld>> weather_forecast;

    int today_weather;
    
    class Worker{
        public:
            int N_type, L, pos, pos2, dist;
            set<int> type;
    };

    vector<Worker> worker;

    class Job{
        public:
            int id, type, N, v, f;
            ld P,d_weather;
            vector<pair<int,ll>> reward; 
            vector<ll> score;
            vector<int> depend;
            vector<ld> weather_task;
    };

    vector<Job> job;

    //caliculate distance
    void dij(){
        dist.resize(V);
        for (int i = 0; i < V; i++){
            dist[i].resize(V);
            for (int j = 0; j < V; j++) dist[i][j]=1e9;
            dist[i][i] = 0;
            priority_queue<pair<int, int>, std::vector<pair<int, int>>, std::greater<pair<int, int>>> q;
            q.push({0, i});
            while(!q.empty()){
                pair<int, int> t = q.top();
                q.pop();
                if (dist[i][t.second] != t.first) continue;
                for (auto e : edge[t.second]){
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
            cin >> job[i].id >> job[i].type >> job[i].N >> job[i].v >> job[i].P >> job[i].d_weather >> job[i].f;
            job[i].id--;
            job[i].type--;
            job[i].v--;
            // if (job[i].f == 1) selected_jobs.push_back(i);
            int N_reward;
            cin >> N_reward;
            for (int j = 0; j < N_reward; j++){
                int f, g;
                cin >> f >> g;
                f--;
                job[i].reward.push_back({f, g});
            }
            job[i].reward.push_back({(int)T_max + 2, job[i].reward[N_reward-1].second});
            job[i].score.resize(T_max+2, 0);
            job[i].score[0] = 0;
            int it = 0;
            for (int j = 0; j < T_max + 1; j++){
                if (it == 0) {
                    job[i].score[j+1]=0;
                    if (j >= job[i].reward[it].first){
                        it++;
                    }
                    continue;
                }
                ll now_score = job[i].reward[it-1].second + (j - job[i].reward[it-1].first)
                    * (job[i].reward[it].second - job[i].reward[it-1].second) / (job[i].reward[it].first - job[i].reward[it-1].first);
                job[i].score[j+1]=job[i].score[j]+now_score;
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
        cin >> T_weather >> N_weather;
        weather_graph.resize(N_weather);
        for (int i = 0; i < N_weather; i++){
            weather_graph[i].resize(N_weather);
            for (int j = 0; j < N_weather; j++){
                cin >> weather_graph[i][j];
            }
        }
        c_weather.resize(N_weather);
        for (int i = 0; i < N_weather; i++) cin >> c_weather[i];
        for (int i = 0; i < N_job; i++){
            for (int j = 0; j < N_weather; j++) job[i].weather_task.push_back(pow((ld)1 - job[i].d_weather, c_weather[j]));
        }
        weather_forecast.resize(T_max / T_weather);
        cin >> P_m >> R_m >> alpha;
        for (int i = 0; i < T_max / T_weather; i++){
            int t_i;
            cin >> t_i;
            weather_forecast[i].resize(N_weather);
            for (int j = 0; j < N_weather; j++){
                cin >> weather_forecast[i][j];
            }
        }
    }

    void interact(int now){
        cin >> today_weather;
        today_weather--;
        int n_job;
        cin >> n_job;
        for (int i = 0; i < n_job; i++){
            int f;
            cin >> f;
            f--;
            cin >> job[f].N;
        }
        for (int i = 0; i < N_worker; i++){
            int id;
            cin >> id;
            id--;
            cin >> worker[id].pos >> worker[id].pos2 >> worker[id].dist;
            worker[id].pos--;
            worker[id].pos2--;
        }
        if (now % T_weather == 0){
            for (int i = now / T_weather; i < T_max / T_weather; i++){
                int t_i;
                cin >> t_i;
                for (int j = 0; j < N_weather; j++) cin >> weather_forecast[i][j];
            }
        }
    }
} IOServer;

struct solver{
    //determine worker's job
    vector<int> worker_job;
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

    void init(){
        worker_jobs.resize(IOServer.N_worker);
        for (int i = 0; i < IOServer.N_worker; i++) {
            worker_jobs[i][0] = {-1, IOServer.worker[i].pos};
        }
        map<int, int> selected_jobs; // {id, finish_time}
        vector<vector<Action>> schejule(IOServer.N_worker, vector<Action>(IOServer.T_max, Action::STAY));
        // selected_jobs に入れる

        // TODO: IOServer.job[x].f == 1 のタスクをやる
        // -> score をINF にしとけばOK？

        deque<int> deq;
        for (int i = 0; i < IOServer.N_job; i++) {
            if (IOServer.job[i].f == 1) {
                deq.push_back(i);
            }
        }
        while (!deq.empty()) {
            int i = deq.front(); deq.pop_front();
            for (auto e : IOServer.job[i].depend) {
                if (IOServer.job[e].f == 0) {
                    IOServer.job[e].f = 1;
                    deq.push_back(e);
                }
            }
        }

        

        for (int loop = 0; loop < 8; loop++) for (int w = 0; w < IOServer.N_worker; w++) {
            priority_queue<Job, vector<Job>, function<bool(Job, Job)>> queue([](Job a, Job b) {
                return a.score < b.score;
            });
            for (int j = 0; j < IOServer.N_job; j++) {
                
                // 嫌だけど これをなくせば強くなるが...
                if (IOServer.job[j].depend.size() != 0) {
                    continue;
                }

                if (selected_jobs.count(j)) continue;
                if (IOServer.worker[w].type.count(IOServer.job[j].type) == 0) continue;
                if (!all_of(all(IOServer.job[j].depend), [&](int d) { return selected_jobs.count(d); })) continue;
                int job_day = (IOServer.job[j].N + IOServer.worker[w].L - 1) / IOServer.worker[w].L + (int)((double)IOServer.worker[w].L * 0.2); // 天気で変動するため +10
                for (
                    int start = IOServer.job[j].reward[0].first + 1;
                    start + job_day < IOServer.job[j].reward[IOServer.job[j].reward.size() - 2].first;
                    start += IOServer.T_max / 30
                ) {
                    ll score = 0, job_N = IOServer.job[j].N;
                    for (int t = start; t <= start + job_day; t++) {
                        score += IOServer.job[j].score[t] * min(job_N, (ll)IOServer.worker[w].L);
                        job_N -= min(job_N, (ll)IOServer.worker[w].L);
                    }
                    if (IOServer.job[j].f == 1) {
                        score += 1000000000LL;
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
                int move_day = IOServer.dist[prev_pos][IOServer.job[job.id].v] + 0;
                if (IOServer.job[job.id].f != 1 && loop < 5 && move_day > (loop + 1) * 5) continue;
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


        set<int> sj;
        for (auto [id, fin] : selected_jobs) {
            sj.insert(id);
        }
        for (int i = 0; i < IOServer.N_job; i++) {
            if (IOServer.job[i].f == 1) {
                sj.insert(i);
            }
        } 
        cout << sj.size() << " ";
        for (int i : sj) cout << i + 1 << " ";
        cout << endl;

        for (int i : sj) IOServer.selected_jobs.push_back(i);

        // worker_job.resize(IOServer.N_worker, -1);
        // for (int i = 0; i < IOServer.selected_jobs.size(); i++){
        //     for (int j : IOServer.job[IOServer.selected_jobs[i]].depend){
        //         if (IOServer.job[j].f == 0) {
        //             IOServer.job[j].f = 1;
        //             IOServer.selected_jobs.push_back(j);
        //         }
        //     }
        // }
        // vector<int> is_selected(IOServer.N_job, 0);
        // for (int i = 0; i < IOServer.N_worker; i++){
        //     for (int j = 0; j < IOServer.N_job; j++){
        //         if (is_selected[j]) continue;
        //         if (IOServer.worker[i].type.find(IOServer.job[j].type) == IOServer.worker[i].type.end()) continue;
        //         if (IOServer.job[j].depend.size() > 0) continue;
        //         is_selected[j] = 1;
        //         worker_job[i] = j;
        //         IOServer.selected_jobs.push_back(j);
        //         break;
        //     }
        // }
        // set<int> sj;
        // for(auto j : IOServer.selected_jobs) sj.emplace(j);
        // cout << sj.size() << " ";
        // for (int i : sj) cout << i + 1 << " ";
        // cout << endl;
    }

    //determine action
    void solve(){
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


        for (int t = 0; t < IOServer.T_max; t++){
            IOServer.interact(t); // 必要！！！
            if (t == 0){
                cout << IOServer.N_worker << endl;
                for (int j = 0; j < IOServer.N_worker; j++) cout << j + 1 << " ";
                cout << endl;
                for (int j = 0; j < IOServer.N_worker; j++){
                    // for (int k = 0; k < IOServer.T_max; k++) cout << worker_job[j] + 1 << " ";
                    for (int k = 0; k < IOServer.T_max; k++) cout << next_job(j, k) + 1 << " ";
                    cout << endl;
                }
            } else {
                cout << 0 << endl;
                cout << endl;
            }

            set<int> finished_jobs_nxt = finished_jobs;
            for (int w = 0; w < IOServer.N_worker; w++) {
                if (worker_job[w] == -1) {
                    cout << "stay" << endl; continue;
                }

                if (IOServer.job[worker_job[w]].v == IOServer.worker[w].pos && IOServer.worker[w].dist == 0) {

                    if (IOServer.job[worker_job[w]].N > 0
                        && IOServer.job[worker_job[w]].reward[0].first < t
                        && t < IOServer.job[worker_job[w]].reward[IOServer.job[worker_job[w]].reward.size() - 2].first
                        && all_of(all(IOServer.job[worker_job[w]].depend), [&](int d) { return finished_jobs.find(d) != finished_jobs.end(); })
                    ) {
                        int task_weight = min(IOServer.job[worker_job[w]].N, (int)(IOServer.worker[w].L * IOServer.job[worker_job[w]].weather_task[IOServer.today_weather]));
                        cout << "execute " << worker_job[w] + 1 << " " << task_weight << endl;
            //             cout << "execute " << worker_job[j] + 1 << " " << min(IOServer.job[worker_job[j]].N, (int)(IOServer.worker[j].L * IOServer.job[worker_job[j]].weather_task[IOServer.today_weather])) << endl;
                        IOServer.job[worker_job[w]].N -= task_weight;
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
                finished_jobs = finished_jobs_nxt;
            }

            // for (int j = 0; j < IOServer.N_worker; j++){
            //     if (IOServer.worker[j].pos == IOServer.job[worker_job[j]].v && IOServer.worker[j].dist == 0){
            //         if (IOServer.job[worker_job[j]].N > 0 && 
            //         IOServer.job[worker_job[j]].score[i+1] - IOServer.job[worker_job[j]].score[i] &&
            //         IOServer.worker[j].L * IOServer.job[worker_job[j]].weather_task[IOServer.today_weather] > 0
            //         ){
            //             cout << "execute " << worker_job[j] + 1 << " " << min(IOServer.job[worker_job[j]].N, (int)(IOServer.worker[j].L * IOServer.job[worker_job[j]].weather_task[IOServer.today_weather])) << endl;
            //         } else {
            //             cout << "stay" << endl;
            //         }
            //     } else {
            //         cout << "move " << IOServer.job[worker_job[j]].v + 1 << endl;
            //     }
            // }

        }
        ll score;
        cin>>score; // read score to avoid TLE
    }
} solver;

int main(int argc, char *argv[]){
    IOServer.input();
    solver.init();
    solver.solve();
}