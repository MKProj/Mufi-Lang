use criterion::{black_box, criterion_group, criterion_main, Criterion};
use mufi_bench::{compile, version};

pub fn bench(c: &mut Criterion){
    let mut group = c.benchmark_group(version());
    group.bench_function("Fibonacci Benchmark", |b| b.iter(|| compile(black_box("/hdd/mufic/src/test/fibonacci.mufi"))));
    group.bench_function("Closure Benchmark", |b| b.iter(|| compile(black_box("test/closures.mufi"))));
    group.bench_function("SuperClass Benchmark", |b|b.iter(|| compile(black_box("test/classes.mufi"))));
    group.finish()
}

criterion_group!(benches, bench);
criterion_main!(benches);
