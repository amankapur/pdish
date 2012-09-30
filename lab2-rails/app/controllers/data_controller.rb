class DataController < ApplicationController

	protect_from_forgery except: "create"
  
	def index
    @data = Datum.all
  end

  def create
    @datum = Datum.new()
		@datum.number = params[:number]
		@datum.opacity = params[:opacity]
	  @datum.save
  	
		respond_to do |format|
		format.html { redirect_to action: 'index'}
		end
  end

	def show
		@datum = Data.find(params[:id])
	end

  def destroy
    @datum = Datum.find(params[:id])
    @datum.destroy
    respond_to do |format|
      format.html { redirect_to data_url }
      format.json { head :no_content }
    end
  end
end
