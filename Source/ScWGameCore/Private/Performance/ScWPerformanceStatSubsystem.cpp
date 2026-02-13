// Scientific Ways

#include "Performance/ScWPerformanceStatSubsystem.h"

#include "Game/ScWGameState.h"

#include "Performance/ScWPerformanceStatTypes.h"
#include "Performance/LatencyMarkerModule.h"

#include "ProfilingDebugging/CsvProfiler.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWPerformanceStatSubsystem)

CSV_DEFINE_CATEGORY(ScWPerformance, /*bIsEnabledByDefault=*/false);

class FSubsystemCollectionBase;

//////////////////////////////////////////////////////////////////////
// FScWPerformanceStatCache

void FScWPerformanceStatCache::StartCharting()
{
}

void FScWPerformanceStatCache::ProcessFrame(const FFrameData& FrameData)
{
	// Record stats about the frame data
	{
		RecordStat(
			EScWDisplayablePerformanceStat::ClientFPS,
			(FrameData.TrueDeltaSeconds != 0.0) ?
			1.0 / FrameData.TrueDeltaSeconds :
			0.0);

		RecordStat(EScWDisplayablePerformanceStat::IdleTime, FrameData.IdleSeconds);
		RecordStat(EScWDisplayablePerformanceStat::FrameTime, FrameData.TrueDeltaSeconds);
		RecordStat(EScWDisplayablePerformanceStat::FrameTime_GameThread, FrameData.GameThreadTimeSeconds);
		RecordStat(EScWDisplayablePerformanceStat::FrameTime_RenderThread, FrameData.RenderThreadTimeSeconds);
		RecordStat(EScWDisplayablePerformanceStat::FrameTime_RHIThread, FrameData.RHIThreadTimeSeconds);
		RecordStat(EScWDisplayablePerformanceStat::FrameTime_GPU, FrameData.GPUTimeSeconds);	
	}

	if (UWorld* World = MySubsystem->GetGameInstance()->GetWorld())
	{
		// Record some networking related stats
		if (const AScWGameState* GameState = World->GetGameState<AScWGameState>())
		{
			RecordStat(EScWDisplayablePerformanceStat::ServerFPS, GameState->GetServerFPS());
		}

		if (APlayerController* LocalPC = GEngine->GetFirstLocalPlayerController(World))
		{
			if (APlayerState* PS = LocalPC->GetPlayerState<APlayerState>())
			{
				RecordStat(EScWDisplayablePerformanceStat::Ping, PS->GetPingInMilliseconds());
			}

			if (UNetConnection* NetConnection = LocalPC->GetNetConnection())
			{
				const UNetConnection::FNetConnectionPacketLoss& InLoss = NetConnection->GetInLossPercentage();
				RecordStat(EScWDisplayablePerformanceStat::PacketLoss_Incoming, InLoss.GetAvgLossPercentage());
				
				const UNetConnection::FNetConnectionPacketLoss& OutLoss = NetConnection->GetOutLossPercentage();
				RecordStat(EScWDisplayablePerformanceStat::PacketLoss_Outgoing, OutLoss.GetAvgLossPercentage());
				
				RecordStat(EScWDisplayablePerformanceStat::PacketRate_Incoming, NetConnection->InPacketsPerSecond);
				RecordStat(EScWDisplayablePerformanceStat::PacketRate_Outgoing, NetConnection->OutPacketsPerSecond);

				RecordStat(EScWDisplayablePerformanceStat::PacketSize_Incoming, (NetConnection->InPacketsPerSecond != 0) ? (NetConnection->InBytesPerSecond / (float)NetConnection->InPacketsPerSecond) : 0.0f);
				RecordStat(EScWDisplayablePerformanceStat::PacketSize_Outgoing, (NetConnection->OutPacketsPerSecond != 0) ? (NetConnection->OutBytesPerSecond / (float)NetConnection->OutPacketsPerSecond) : 0.0f);
			}
			
			// Finally, record some input latency related stats if they are enabled
			TArray<ILatencyMarkerModule*> LatencyMarkerModules = IModularFeatures::Get().GetModularFeatureImplementations<ILatencyMarkerModule>(ILatencyMarkerModule::GetModularFeatureName());
			for (ILatencyMarkerModule* LatencyMarkerModule : LatencyMarkerModules)
			{
				if (LatencyMarkerModule->GetEnabled())
				{
					const float TotalLatencyMs = LatencyMarkerModule->GetTotalLatencyInMs();
					if (TotalLatencyMs > 0.0f)
					{
						// Record some stats about the latency of the game
						RecordStat(EScWDisplayablePerformanceStat::Latency_Total, TotalLatencyMs);
						RecordStat(EScWDisplayablePerformanceStat::Latency_Game, LatencyMarkerModule->GetGameLatencyInMs());
						RecordStat(EScWDisplayablePerformanceStat::Latency_Render, LatencyMarkerModule->GetRenderLatencyInMs());

						// Record some CSV profile stats.
						// You can see these by using the following commands
						// Start and stop the profile:
						//	CsvProfile Start
						//	CsvProfile Stop
						//
						// Or, you can profile for a certain number of frames:
						// CsvProfile Frames=10
						//
						// And this will output a .csv file to the Saved\Profiling\CSV folder
#if CSV_PROFILER
						if (FCsvProfiler* Profiler = FCsvProfiler::Get())
						{
							static const FName TotalLatencyStatName = TEXT("ScW_Latency_Total");
							Profiler->RecordCustomStat(TotalLatencyStatName, CSV_CATEGORY_INDEX(ScWPerformance), TotalLatencyMs, ECsvCustomStatOp::Set);

							static const FName GameLatencyStatName = TEXT("ScW_Latency_Game");
							Profiler->RecordCustomStat(GameLatencyStatName, CSV_CATEGORY_INDEX(ScWPerformance), LatencyMarkerModule->GetGameLatencyInMs(), ECsvCustomStatOp::Set);

							static const FName RenderLatencyStatName = TEXT("ScW_Latency_Render");
							Profiler->RecordCustomStat(RenderLatencyStatName, CSV_CATEGORY_INDEX(ScWPerformance), LatencyMarkerModule->GetRenderLatencyInMs(), ECsvCustomStatOp::Set);
						}
#endif

						// Some more fine grain latency numbers can be found on the marker module if desired
						//LatencyMarkerModule->GetRenderLatencyInMs()));
						//LatencyMarkerModule->GetDriverLatencyInMs()));
						//LatencyMarkerModule->GetOSRenderQueueLatencyInMs()));
						//LatencyMarkerModule->GetGPURenderLatencyInMs()));
						break;	
					}
				}
			}
		}
	}
}

void FScWPerformanceStatCache::StopCharting()
{
}

void FScWPerformanceStatCache::RecordStat(const EScWDisplayablePerformanceStat Stat, const double Value)
{
	PerfStateCache.FindOrAdd(Stat).RecordSample(Value);
}

double FScWPerformanceStatCache::GetCachedStat(EScWDisplayablePerformanceStat Stat) const
{
	static_assert((int32)EScWDisplayablePerformanceStat::Count == 18, "Need to update this function to deal with new performance stats");

	if (const FSampledStatCache* Cache = GetCachedStatData(Stat))
	{
		return Cache->GetLastCachedStat();
	}

	return 0.0;
}

const FSampledStatCache* FScWPerformanceStatCache::GetCachedStatData(const EScWDisplayablePerformanceStat Stat) const
{
	static_assert((int32)EScWDisplayablePerformanceStat::Count == 18, "Need to update this function to deal with new performance stats");
	
	return PerfStateCache.Find(Stat);
}

//////////////////////////////////////////////////////////////////////
// UScWPerformanceStatSubsystem

void UScWPerformanceStatSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Tracker = MakeShared<FScWPerformanceStatCache>(this);
	GEngine->AddPerformanceDataConsumer(Tracker);
}

void UScWPerformanceStatSubsystem::Deinitialize()
{
	GEngine->RemovePerformanceDataConsumer(Tracker);
	Tracker.Reset();
}

double UScWPerformanceStatSubsystem::GetCachedStat(EScWDisplayablePerformanceStat Stat) const
{
	return Tracker->GetCachedStat(Stat);
}

const FSampledStatCache* UScWPerformanceStatSubsystem::GetCachedStatData(const EScWDisplayablePerformanceStat Stat) const
{
	return Tracker->GetCachedStatData(Stat);
}

